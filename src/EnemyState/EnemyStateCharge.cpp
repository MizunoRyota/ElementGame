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
}

EnemyStateKind EnemyStateCharge::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		int enemy_dodgechose = GetRand(1);

		if (enemy_dodgechose == 0)      return EnemyStateKind::STATE_RUNLEFT;
		else if (enemy_dodgechose == 1) return EnemyStateKind::STATE_RUNRIGHT;
	}
	else
	{
		return ChangeStateOnDamage();
	}

	return ObjectAccessor::GetObjectAccessor().GetEnemyStateKind();

}
