#pragma once
#include "EnemyAnimationBase.hpp"
class ChaseAnimation : public EnemyAnimationBase
{
public:
	ChaseAnimation(int modelhandle);
	~ChaseAnimation();

private:
	static constexpr float AnimationSpeed = 0.50f;
};
