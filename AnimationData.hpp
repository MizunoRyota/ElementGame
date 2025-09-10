#pragma once
#include <string>

struct  AnimationState
{
	int		anim_kind = -1;				// アニメーションの名前
	int		anim_animnum = 0;			// 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float	anim_totaltime = 0;			// 再生しているアニメーションの再生時間
	float   anim_nowtime = 0;			// 現在のアニメーション再時間
	float	anim_playspeed = 0;			// アニメーションを進める速さ
	bool	anim_isloop = false;		// ループさせるアニメーションかどうか
	int		anim_attachindex = -1;		// アニメーションのインデックス
};