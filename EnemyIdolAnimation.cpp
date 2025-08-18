#include "EnemyIdolAnimation.hpp"

EnemyIdolAnimation::EnemyIdolAnimation(int modelhandle)
	:EnemyAnimationBase(modelhandle)
{
	currentState.AnimationNum = static_cast<int>(AnimKind::Idle);
	currentState.AnimTime = 0;
	currentState.PlayAnimSpeed = AnimationSpeed;
	currentState.TotalAnimationTime = 0;
}
EnemyIdolAnimation::~EnemyIdolAnimation()
{
}