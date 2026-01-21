#include "../stdafx.hpp"
#include "EnemyStateStun.hpp"
#include "../EnemyStateBase.hpp"
#include "../EffectCreator.hpp"
#include "../ObjectAccessor.hpp"
EnemyStateStun::EnemyStateStun()
{
	stun_time = 0;
}
EnemyStateStun::~EnemyStateStun()
{
}
void EnemyStateStun::Enter()
{
	stun_time = STUN_TIME;
    EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::EnemyStun, VAdd(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(),VGet(0, STUN_HEIGHT,0)));
}
void EnemyStateStun::Update()
{
	stun_time -= STUN_DECREASE_TIME;
    EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::EnemyStun, VAdd(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), VGet(0, STUN_HEIGHT, 0)));
}
void EnemyStateStun::Exit()
{
    EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EnemyStun);
}
EnemyStateKind EnemyStateStun::GetNextState()
{
	if (stun_time <= 0)
	{
		return EnemyStateKind::STATE_CHARGE;
	}
	else
	{
		return ChangeStateOnDamage();
	}
	return EnemyStateKind::STATE_STUN;
}