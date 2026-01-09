#include "../stdafx.hpp"
#include "EnemyStateSpecialCharge.hpp"
#include "../ObjectAccessor.hpp"
#include"../src/Sounds/SoundManager.hpp"

EnemyStateSpecialCharge::EnemyStateSpecialCharge()
{
	specialattack_charge_time = 0;
}

EnemyStateSpecialCharge::~EnemyStateSpecialCharge()
{
}

void EnemyStateSpecialCharge::Enter()
{
	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::Barrior, ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::EnemyCharge, ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
	specialattack_charge_time = SPECIALATTACK_CHARGE_TIME;
	SoundManager::GetSoundManager().PlayChargeSpecialSe();
}
void EnemyStateSpecialCharge::Update()
{
	specialattack_charge_time -= SPECIALATTACK_CHARGE_DECREACENUM;
    EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::Barrior, ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
    EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::EnemyCharge, ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
}
void EnemyStateSpecialCharge::Exit()
{
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Barrior);
    EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EnemyCharge);
}

EnemyStateKind EnemyStateSpecialCharge::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak())
	{
		return EnemyStateKind::STATE_STUN;
	}
	if (specialattack_charge_time <= 0)
	{
		return EnemyStateKind::STATE_SPECIALATTACK;
	}
	else
	{
		return EnemyStateKind::STATE_SPECIAL_CHARGE;
	}
}