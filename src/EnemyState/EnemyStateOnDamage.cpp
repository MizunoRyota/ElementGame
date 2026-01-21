#include "../stdafx.hpp"
#include "EnemyStateOnDamage.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateOnDamage::EnemyStateOnDamage()
{
}

EnemyStateOnDamage::~EnemyStateOnDamage()
{
}

EnemyStateKind EnemyStateOnDamage::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		return EnemyStateKind::STATE_CHOSEATTACK;
	}
	return EnemyStateKind::STATE_ONDAMAGE;
};