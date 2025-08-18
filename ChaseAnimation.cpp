#include "Dxlib.h"
#include "ChaseAnimation.hpp"
ChaseAnimation::ChaseAnimation(int modelhandle)
	:EnemyAnimationBase(modelhandle)
{
	currentState.AnimationNum = static_cast<int>(AnimKind::Run);
	currentState.AnimTime = 0;
	currentState.PlayAnimSpeed = AnimationSpeed;
	currentState.TotalAnimationTime = 0;
}

ChaseAnimation::~ChaseAnimation()
{
}