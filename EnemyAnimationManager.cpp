#include "Dxlib.h"
#include "EnemyAnimationManager.hpp"

EnemyAnimationManager::EnemyAnimationManager(int modelhadle)
{
	this->modelHandle = modelhadle;
	animater = std::make_shared<EnemyAnimationBase>(modelhadle);
	animater->InitializeAnimationData();
	prev_state = animater.get()->GetCurrentState();
	animater->ChangeMotion(animater.get()->GetCurrentState());
}
EnemyAnimationManager::~EnemyAnimationManager()
{
}

void EnemyAnimationManager::Initialize()
{
	prev_state = animater.get()->GetCurrentState();
	animater->ChangeMotion(animater.get()->GetCurrentState());
}

void EnemyAnimationManager::Update()
{
	animater->Update(prev_state,animater.get()->GetCurrentState());
}

void EnemyAnimationManager::ChangeAnimation(int animation_num)
{

}