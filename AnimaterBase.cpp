#include"DxLib.h"
#include<cmath>
#include<typeinfo>
#include "AnimationData.hpp"
#include"AnimaterBase.hpp"

AnimaterBase::AnimaterBase(int modelhandle)
	:animBlendRate(1.0f)
	, modelHandle(0)
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
	this->modelHandle = modelhandle;
}
AnimaterBase::~AnimaterBase()
{
}

void AnimaterBase::InitializeAnimationData()
{}

void AnimaterBase::ChangeMotion(AnimationState nextstate)
{
	
	if (currentState.AnimationKind == nextstate.AnimationKind)
	{
		return;
	}

	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (prevState.AttatchIndex != -1)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(modelHandle, prevState.AttatchIndex);
		prevState.AttatchIndex = -1;
	}

	// 今まで再生中のモーションだったものの情報をPrevに移動する
	prevState= currentState;

	//新しいアタッチ番号を保存
	currentState = nextstate;
	currentState.AttatchIndex = MV1AttachAnim(modelHandle, currentState.AnimationNum);
	currentState.TotalAnimationTime = MV1GetAnimTotalTime(modelHandle, currentState.AttatchIndex);

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	animBlendRate = prevState.AttatchIndex == -1 ? 1.0f : 0.0f;
}

void AnimaterBase::UpdateAnimation()
{

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
	if (currentState.AttatchIndex != -1)
	{
		//アニメーションを進める

		currentState.AnimTime += currentState.PlayAnimSpeed;

		// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		if (currentState.AnimTime > currentState.TotalAnimationTime)
		{
			if (currentState.animaton_isloop)
			{
				//currentState.AnimTime = static_cast<float>(fmod(currentState.AnimTime, animationTotalTime));
				currentState.AnimTime = 0;
			}
		}
		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, currentState.AttatchIndex, currentState.AnimTime);
		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, currentState.AttatchIndex, animBlendRate);
	}
	// 再生しているアニメーション２の処理
	if (prevState.AttatchIndex != -1)
	{

		// 再生時間を進める
		prevState.AnimTime += prevState.PlayAnimSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (prevState.AnimTime > prevState.TotalAnimationTime)
		{
			prevState.AnimTime = static_cast<float>(fmod(prevState.AnimTime, prevState.TotalAnimationTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, prevState.AttatchIndex, prevState.AnimTime);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, prevState.AttatchIndex, 1.0f - animBlendRate);
	}
}

void AnimaterBase::DetachAnimation()
{
	//アニメーションのデタッチ
	MV1DetachAnim(modelHandle, currentState.AttatchIndex);
}
