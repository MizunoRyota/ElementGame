#include "../stdafx.hpp"
#include "EnemyStateSpecialAttack.hpp"
#include "../BulletFire.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateSpecialAttack::EnemyStateSpecialAttack()
{
}
EnemyStateSpecialAttack::~EnemyStateSpecialAttack()
{
}
void EnemyStateSpecialAttack::Enter()
{
	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::Barrior, ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
}
void EnemyStateSpecialAttack::Update()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimationFrame() == SPECIALEATTACK_TIMING)
	{
		EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::Roar, ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
		enemy_bullet->FireSpecialAttack(ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition(), ObjectAccessor::GetObjectAccessor().GetCameraDirection(), SPECIALBULLET_SPEED);
	}
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::Barrior, ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
}
void EnemyStateSpecialAttack::Exit()
{
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Barrior);

}
EnemyStateKind EnemyStateSpecialAttack::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		return EnemyStateKind::STATE_CHARGE;
	}
	else
	{
		return EnemyStateKind::STATE_SPECIALATTACK;
	}
}