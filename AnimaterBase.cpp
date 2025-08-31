#include "stdafx.hpp"

#include "AnimationData.hpp"
#include"AnimaterBase.hpp"

AnimaterBase::AnimaterBase(int anim_modelhandle)
	:anim_blendrate(1.0f)
	, anim_modelhandle(0)
	, anim_isend(false)
{
	////アニメーションのステート初期化
	this->anim_prevstate.anim_animnum = -1;
	this->anim_prevstate.anim_nowtime = 0;
	this->anim_prevstate.anim_playspeed = 0;
	this->anim_prevstate.anim_totaltime = 0;
	this->anim_currentstate.anim_animnum = 0;
	this->anim_currentstate.anim_nowtime = 0;
	this->anim_currentstate.anim_playspeed = 0;
	this->anim_currentstate.anim_totaltime = 0;
	this->anim_modelhandle = anim_modelhandle;
}
AnimaterBase::~AnimaterBase()
{
}

void AnimaterBase::InitializeAnimationData()
{
}

void AnimaterBase::ChangeMotion(AnimationState nextstate)
{

	if (anim_currentstate.anim_kind == nextstate.anim_kind)
	{
		return;
	}

	anim_isend = false;

	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (anim_prevstate.anim_attachindex != -1)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(anim_modelhandle, anim_prevstate.anim_attachindex);
		anim_prevstate.anim_attachindex = -1;
	}

	// 今まで再生中のモーションだったものの情報をPrevに移動する
	anim_prevstate = anim_currentstate;

	//新しいアタッチ番号を保存
	anim_currentstate = nextstate;
	anim_currentstate.anim_attachindex = MV1AttachAnim(anim_modelhandle, anim_currentstate.anim_animnum);
	anim_currentstate.anim_totaltime = MV1GetAnimTotalTime(anim_modelhandle, anim_currentstate.anim_animnum);

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	anim_blendrate = anim_prevstate.anim_attachindex == -1 ? 1.0f : 0.0f;
}

void AnimaterBase::UpdateAnimation()
{

	// ブレンド率が１以下の場合は１に近づける
	if (anim_blendrate < 1.0f)
	{
		anim_blendrate += ANIM_BLEND_SPEED;
		if (anim_blendrate > 1.0f)
		{
			anim_blendrate = 1.0f;
		}
	}

	//再生しているアニメーションの処理１
	if (anim_currentstate.anim_attachindex != -1)
	{
		//アニメーションを進める
		anim_nowframe += anim_currentstate.anim_playspeed;
		anim_currentstate.anim_nowtime += anim_currentstate.anim_playspeed;

		// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		if (anim_currentstate.anim_nowtime > anim_currentstate.anim_totaltime)
		{
			anim_isend = true;
			anim_nowframe = 0;
			if (anim_currentstate.anim_isloop)
			{
				//anim_currentstate.anim_nowtime = static_cast<float>(fmod(anim_currentstate.anim_nowtime, animationTotalTime));
				anim_currentstate.anim_nowtime = 0;
			}
		}
		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(anim_modelhandle, anim_currentstate.anim_attachindex, anim_currentstate.anim_nowtime);
		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(anim_modelhandle, anim_currentstate.anim_attachindex, anim_blendrate);
	}
	// 再生しているアニメーション２の処理
	if (anim_prevstate.anim_attachindex != -1)
	{

		// 再生時間を進める
		anim_prevstate.anim_nowtime += anim_prevstate.anim_playspeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (anim_prevstate.anim_nowtime > anim_prevstate.anim_totaltime)
		{
			anim_prevstate.anim_nowtime = static_cast<float>(fmod(anim_prevstate.anim_nowtime, anim_prevstate.anim_totaltime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(anim_modelhandle, anim_prevstate.anim_attachindex, anim_prevstate.anim_nowtime);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(anim_modelhandle, anim_prevstate.anim_attachindex, 1.0f - anim_blendrate);
	}
}