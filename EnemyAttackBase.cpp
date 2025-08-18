#include "Dxlib.h"
#include "EnemyAttackBase.hpp"

EnemyAttackBase::EnemyAttackBase(int modelhandle)
	: isattack_jumpattack(false)
	, enemy_position(VGet(0, 0, 0))
	, player_position(VGet(0, 0, 0))
	, flame_name (0)
{
	this->model_handle = modelhandle;
	flame_name = MV1SearchFrame(model_handle, "m1.R");
}

EnemyAttackBase::~EnemyAttackBase()
{
}

void EnemyAttackBase::Initialize()
{

}


void EnemyAttackBase::DebugDraw()
{ 

}

void EnemyAttackBase::PlayEffect()
{

}

void EnemyAttackBase::UpdateBullet()
{

}