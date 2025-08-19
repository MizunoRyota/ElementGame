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
	void ChangeAnimation(int animation_num);
private:
	std::shared_ptr<EnemyAnimationBase> animater ;
	EnemyAnimationBase::AnimationState prevState ;
	EnemyAnimationBase::AnimationState newState;
	int modelHandle;
};