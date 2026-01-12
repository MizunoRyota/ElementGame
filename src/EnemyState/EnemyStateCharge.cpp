#include "../stdafx.hpp"
#include "EnemyStateCharge.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"
EnemyStateCharge::EnemyStateCharge()
{
}

EnemyStateCharge::~EnemyStateCharge()
{
}

void EnemyStateCharge::Enter()
{
	ChoseAttackState();
}

EnemyStateKind EnemyStateCharge::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyHp()<= ENEMY_FLOAT_TIMING 
		&& !ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak()
		&& !ObjectAccessor::GetObjectAccessor().GetCrystalIsInit())
	{
		return EnemyStateKind::STATE_FLOAT;
	}
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		int enemy_dodgechose = GetRand(1);

		if (enemy_dodgechose == 0)      return EnemyStateKind::STATE_RUNLEFT;
		else if (enemy_dodgechose == 1) return EnemyStateKind::STATE_RUNRIGHT;
	}
	else
	{
		return EnemyStateKind::STATE_CHARGE;
	}

	return EnemyStateKind::STATE_CHARGE;

}