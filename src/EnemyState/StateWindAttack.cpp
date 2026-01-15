#include "../stdafx.hpp"
#include "StateWindAttack.hpp"
#include "../BulletFire.hpp"
#include "../ObjectAccessor.hpp"


StateWindAttack::StateWindAttack()
{
}

StateWindAttack::~StateWindAttack()
{
}

void StateWindAttack::Enter()
{

}

void StateWindAttack::Update()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimationFrame() == WINDATTACK_TIMING)
	{
		enemy_bullet->FireHoming(ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyDirection(), WINDBULLET_SPEED);
	}
	enemy_bullet->FireUpdate(); // íeÉNÅ[Éã

}

EnemyStateKind StateWindAttack::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		return EnemyStateKind::STATE_CHOSEATTACK;
	}
	else
	{
		return EnemyStateKind::STATE_WINDATTACK;
	}
}