#pragma once
#include "EnemyAnimationBase.hpp"

class EnemyIdolAnimation : public EnemyAnimationBase
{
public:
	EnemyIdolAnimation(int modelhandle);
	~EnemyIdolAnimation();
private:
	static constexpr float AnimationSpeed = 0.35f;
};

