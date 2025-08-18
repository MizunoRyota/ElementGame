#pragma once
#include <memory>
#include <vector>
#include "EnemyAnimationBase.hpp"
class EnemyAnimationManager
{
public:
	EnemyAnimationManager(int modelhandle);
	~EnemyAnimationManager();
	void Initialize();
	void Update();
private:
	std::shared_ptr<EnemyAnimationBase> currentState ;
	EnemyAnimationBase::AnimationState prevState ;
	EnemyAnimationBase::AnimationState newState;
	int modelHandle;
};