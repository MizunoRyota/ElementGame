#include "../stdafx.hpp"
#include "EnemyStateIdle.hpp"
#include "../ObjectAccessor.hpp"
EnemyStateIdle::EnemyStateIdle()
{
}

EnemyStateIdle::~EnemyStateIdle()
{
}

EnemyStateKind EnemyStateIdle::GetNextState() 
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		return EnemyStateKind::STATE_IDLE;
	}
	return EnemyStateKind::STATE_IDLE;
};