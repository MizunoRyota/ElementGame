#include "../stdafx.hpp"
#include "StateWaterAttack.hpp"
#include "../BulletFire.hpp"
#include "../ObjectAccessor.hpp"


StateWaterAttack::StateWaterAttack()
{
}

StateWaterAttack::~StateWaterAttack()
{
}

void StateWaterAttack::Enter()
{

}

void StateWaterAttack::Update()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimationFrame() == WATERATTACK_TIMING)
	{
		// Enemy.cppÇÃSetAttackPosition()Ç≈çsÇÌÇÍÇƒÇ¢ÇΩçÇÇ≥ï‚ê≥Çâ¡Ç¶ÇÈ
		VECTOR firePos = ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition();
		firePos.y += BULLET_HIGHT;

		enemy_bullet->FireDiffusion(firePos, ObjectAccessor::GetObjectAccessor().GetEnemyDirection(), WATERBULLET_SPEED);
	}
	enemy_bullet->FireUpdate(); // íeÉNÅ[Éã

}

EnemyStateKind StateWaterAttack::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		return EnemyStateKind::STATE_CHOSEATTACK;
	}
	else
	{
		return ChangeStateOnDamage();
	}

	return EnemyStateKind::STATE_WATERATTACK;
}