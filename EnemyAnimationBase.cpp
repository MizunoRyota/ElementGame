#include"DxLib.h"
#include<cmath>
#include"EnemyAnimationBase.hpp"

EnemyAnimationBase::EnemyAnimationBase(int modelhandle)
	:animBlendRate(1.0f)
	,modelHandle(0)
	,effect_isplayAnim(false)
{
	////アニメーションのステート初期化
	this->prevState.AnimationNum = -1;
	this->prevState.AnimTime = 0;
	this->prevState.PlayAnimSpeed = 0;
	this->prevState.TotalAnimationTime = 0;
	this->currentState.AnimationNum = 0;
	this->currentState.AnimTime = 0;
	this->currentState.PlayAnimSpeed = 0;
	this->currentState.TotalAnimationTime = 0;
	this->newState.AnimationNum = 0;
	this->newState.AnimTime = 0;
	this->newState.PlayAnimSpeed = 0;
	this->newState.TotalAnimationTime = 0;
	this->modelHandle = modelhandle;
}
EnemyAnimationBase::~EnemyAnimationBase()
{}
void EnemyAnimationBase::Initialize(AnimationState state ,int animnum)
{}

void EnemyAnimationBase::Update(AnimationState prevstate, AnimationState newstate)
{
	UpdateAnimation(prevstate, newstate);
	DetachAnimation(newstate);
	SwitchAnimation(newstate);
}

void EnemyAnimationBase::ChangeMotion(AnimationState newstate)
{
	if (!effect_isplayAnim)
	{
		//再生しているフラグをTRUEにする
		effect_isplayAnim = true;

		// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
		if (prevState.AnimationNum != -1)
		{
			//アニメーションのデタッチ
			MV1DetachAnim(modelHandle, prevState.AnimationNum);
			prevState.AnimationNum = -1;
		}

		// 今まで再生中のモーションだったものの情報をPrevに移動する
		prevState.AnimationNum = currentState.AnimationNum;
		prevState.TotalAnimationTime = currentState.TotalAnimationTime;

		//新しいアタッチ番号を保存
		currentState.AnimationNum = MV1AttachAnim(modelHandle, (newstate.AnimationNum));

		currentState.AnimTime = 0;

		// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
		animBlendRate = prevState.AnimationNum == -1 ? 1.0f : 0.0f;
	}
}

void EnemyAnimationBase::UpdateAnimation(AnimationState prevstate, AnimationState currentstate)
{
	// 再生しているアニメーションの総時間
	 float animationTotalTime = 0;

	// ブレンド率が１以下の場合は１に近づける
	if (animBlendRate < 1.0f)
	{
		animBlendRate += AnimBlendSpeed;
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}
	//再生しているアニメーションの処理１
	if ( currentstate.AnimationNum!= -1)
	{
		// アニメーションの総時間を取得
		animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentstate.AnimationNum);

		//アニメーションを進める
	
		currentState.AnimTime += currentState.PlayAnimSpeed;

		// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		if (currentState.AnimTime > animationTotalTime)
		{
			currentState.AnimTime = static_cast<float>(fmod(currentState.AnimTime, animationTotalTime));
			//再生しているフラグをFALSEにする
			effect_isplayAnim = false;
		}
		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, currentstate.AnimationNum, currentState.AnimTime);
		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, currentstate.AnimationNum, animBlendRate);
	}
	// 再生しているアニメーション２の処理
	if (prevstate.AnimationNum != -1)
	{
		// アニメーションの総時間を取得
		animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, prevstate.AnimationNum);

		// 再生時間を進める
		prevState.AnimTime += prevstate.PlayAnimSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (prevState.AnimTime > animationTotalTime)
		{
			prevState.AnimTime = static_cast<float>(fmod(prevstate.AnimTime, animationTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, prevstate.AnimationNum, prevState.AnimTime);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, prevstate.AnimationNum, 1.0f - animBlendRate);
	}
}

void EnemyAnimationBase::DetachAnimation(AnimationState newstate)
{
	if (!effect_isplayAnim)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(modelHandle, currentState.AnimationNum);
	}
}

void EnemyAnimationBase::SwitchAnimation(AnimationState newstate)
{
	if (!effect_isplayAnim)
	{
		ChangeMotion(newstate);
	}
}