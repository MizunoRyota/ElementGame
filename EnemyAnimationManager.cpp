#include "Dxlib.h"
#include "EnemyAnimationManager.hpp"
#include "EnemyIdolAnimation.hpp"
#include "ChaseAnimation.hpp"
EnemyAnimationManager::EnemyAnimationManager(int modelhadle)
{
	this->modelHandle = modelhadle;
	currentState = std::make_shared<ChaseAnimation>(modelhadle);
	prevState = currentState.get()->GetCurrentState();
	currentState->ChangeMotion(currentState.get()->GetCurrentState());
}
EnemyAnimationManager::~EnemyAnimationManager()
{
}

void EnemyAnimationManager::Initialize()
{
	prevState = currentState.get()->GetCurrentState();
	currentState->ChangeMotion(currentState.get()->GetCurrentState());
}

void EnemyAnimationManager::Update()
{
	currentState->Update(prevState,currentState.get()->GetCurrentState());
}