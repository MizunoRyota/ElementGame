#pragma once
#include <string>

struct  AnimationState
{
	int		AnimationKind = -1;
	int		AnimationNum = 0;				// 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float	TotalAnimationTime = 0;			// 再生しているアニメーションの再生時間
	float   AnimTime = 0;					// 現在のアニメーション再時間
	float	PlayAnimSpeed = 0;				// アニメーションを進める速さ
	bool	animaton_isloop = false;
	int		AttatchIndex = -1;
};