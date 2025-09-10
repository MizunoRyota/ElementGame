#pragma once

#include "AnimationData.hpp"
class AnimaterBase
{
public:
	AnimaterBase(int anim_modelhandle);
	virtual~AnimaterBase();
public:

	virtual void InitializeAnimationData() = 0;		//アニメーションの初期化

	virtual void Update() = 0;		//全体の更新
	
	void ChangeMotion(AnimationState nextstate);	//アニメーションの変更
	
	void UpdateAnimation();		//アニメーションの更新
	
	virtual void SwitchAnimation() = 0;		//アニメーションの変更

	const float& GetAmimFrame() const { return anim_currentstate.anim_nowtime; }	//アニメーションの現在の時間を返す

	const bool& GetAmimIsEnd() const { return anim_isend; }		//アニメーションが終わったかどうかを返す

protected:

	static constexpr float	ANIM_BLEND_SPEED = 0.1f;		// アニメーションのブレンド率変化速度

	float		anim_blendrate;					// 現在と過去のアニメーションのブレンド率
	float		anim_nowframe;					// アニメーションの現在の再生時間

	bool		anim_isend;						//　アニメーションのが終わったかどうか

	int			anim_modelhandle;				// アニメーションをつけるモデルハンドル

	AnimationState anim_prevstate;				// ひとつ前の状態
	AnimationState anim_currentstate;			// 現在の状態

	std::unordered_map<int, AnimationState>	animation_data;	//アニメーションの入ったコンテナ
};