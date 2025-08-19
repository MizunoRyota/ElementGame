#pragma once
#pragma once
#include <unordered_map>
#include "AnimationData.hpp"
class AnimaterBase
{
public:
	AnimaterBase(int modelhandle);
	virtual~AnimaterBase();
public:

	virtual void InitializeAnimationData() = 0;
	virtual void Update() = 0;
	void ChangeMotion(AnimationState nextstate);
	void UpdateAnimation();
	void DetachAnimation();
	virtual void SwitchAnimation() = 0;

protected:
	// プレイヤー関係の定義
	static constexpr float	AnimBlendSpeed = 0.1f;		// アニメーションのブレンド率変化速度
	float		animBlendRate;				// 現在と過去のアニメーションのブレンド率
	int			modelHandle;				// 敵のモデルハンドル	
	AnimationState prevState;				// ひとつ前の状態
	AnimationState currentState;			// 現在の状態
	std::unordered_map<int, AnimationState>	animation_data;

};