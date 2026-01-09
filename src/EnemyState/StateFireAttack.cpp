#include "../stdafx.hpp"
#include "../ObjectAccessor.hpp"
#include "StateFireAttack.hpp"
#include "../BulletFire.hpp"

StateFireAttack::StateFireAttack()
{
}

StateFireAttack::~StateFireAttack()
{
}

void StateFireAttack::Enter()
{

}

void StateFireAttack::Update()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimationFrame() == FIREATTACK_TIMING)
	{
		enemy_bullet->FireStraight(ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyDirection(), FIREBULLET_SPEED);
	}
	enemy_bullet->FireUpdate(); // íeÉNÅ[Éã

}

EnemyStateKind StateFireAttack::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		return EnemyStateKind::STATE_CHARGE;
	}
	else
	{
		return EnemyStateKind::STATE_FIREATTACK;
	}
}