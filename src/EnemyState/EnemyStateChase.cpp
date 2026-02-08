#include "../stdafx.hpp"
#include "EnemyStateChase.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateChase::EnemyStateChase(VECTOR& position)
    :chase_position(position)
	,chase_range(0)
	, enemy_hand_effect_handle(-1)
{
}

EnemyStateChase::~EnemyStateChase()
{
}

void EnemyStateChase::Enter()
{
	ChoseRange();
	StartHandEffectForAttack();
}

void EnemyStateChase::ChoseRange()
{
	if (enemy_attack_state == EnemyStateKind::STATE_FIREATTACK)
	{
		chase_range = FIRE_RANGE;
	}
	else if (enemy_attack_state == EnemyStateKind::STATE_WATERATTACK)
	{
		chase_range = WATER_RANGE;
	}
	else if (enemy_attack_state == EnemyStateKind::STATE_WINDATTACK)
	{
		chase_range = WIND_RANGE;
	}
	else if (enemy_attack_state == EnemyStateKind::STATE_JUMPATTACK)
	{
		chase_range = JUMPATTACK_RANGE;
	}
}

EffectCreator::EffectType EnemyStateChase::MapEffectTypeForAttack(float chase_range) const
{
	if (chase_range == FIRE_RANGE)
	{
		return EffectCreator::EffectType::BulletFire;		// 火
	}
	else if (chase_range == WATER_RANGE)
	{
		return EffectCreator::EffectType::BulletWater;		// 水
	}
	else if (chase_range == WIND_RANGE)
	{
		return EffectCreator::EffectType::BulletWind;		// 風
	}
	else if (chase_range == JUMPATTACK_RANGE)
	{
		return EffectCreator::EffectType::JumpAttack;		// 風
	}
	else
	{
		return EffectCreator::EffectType::BulletSpecial;					// 特殊
	}
}

void EnemyStateChase::Update()
{

	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), chase_position);

	// プレイヤーに向かって進む方向を単位ベクトルで求める
	VECTOR checkDirection = VNorm(keepDistance);

	// 敵が進む距離（移動速度に基づく）
	VECTOR chaseVector = VScale(checkDirection, MOVE_SPEED);

	chaseVector.y = 0;

	// 敵の位置を更新
	chase_position = VAdd(chase_position, chaseVector);

	UpdateEffectHandle();

}

bool EnemyStateChase::RangeWithin()
{
	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), chase_position);
	float checkDistance = VSquareSize(keepDistance); // 距離の二乗
	float rangeSquared = (chase_range * chase_range);
	return checkDistance <= rangeSquared;
}

void EnemyStateChase::Exit()
{
	EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::ReadyAttack, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition());
	StopHandEffect();
}

EnemyStateKind EnemyStateChase::GetNextState()
{
	if (RangeWithin())
	{
		return GetEnemyAttackState();
	}
	else
	{
		return ChangeStateOnDamage();
	}
		return EnemyStateKind::STATE_CHASE;
}