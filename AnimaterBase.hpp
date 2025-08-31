#pragma once
#pragma once
#include <unordered_map>
#include "AnimationData.hpp"
class AnimaterBase
{
public:
	AnimaterBase(int anim_modelhandle);
	virtual~AnimaterBase();
public:

	virtual void InitializeAnimationData() = 0;

	virtual void Update() = 0;
	
	void ChangeMotion(AnimationState nextstate);
	
	void UpdateAnimation();
	
	virtual void SwitchAnimation() = 0;

	//
	const float& GetAmimFrame() const { return anim_currentstate.anim_nowtime; }

	const bool& GetAmimIsEnd() const { return anim_isend; }

protected:
	// プレイヤー関係の定義
	static constexpr float	ANIM_BLEND_SPEED = 0.1f;		// アニメーションのブレンド率変化速度

	float		anim_blendrate;				// 現在と過去のアニメーションのブレンド率
	int			anim_modelhandle;				// 
	float		anim_nowframe;
	bool		anim_isend;
	AnimationState anim_prevstate;				// ひとつ前の状態
	AnimationState anim_currentstate;			// 現在の状態
	std::unordered_map<int, AnimationState>	animation_data;
};