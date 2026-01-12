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
	else
	{
		return EffectCreator::EffectType::BulletSpecial;					// 特殊
	}
}

// 手エフェクトを攻撃に応じて再生
void EnemyStateChase::StartHandEffectForAttack()
{
	// 既に同攻撃のエフェクトが再生中なら何もしない
	if (enemy_hand_effect_handle >= 0) return;

	// いったん停止
	StopHandEffect();

	const auto effType = MapEffectTypeForAttack(chase_range);
	enemy_hand_effect_handle = EffectCreator::GetEffectCreator().PlayReturn(effType, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition());
}

void EnemyStateChase::UpdateEffectHandle()
{
	if (enemy_hand_effect_handle >= 0)
	{
		SetPosPlayingEffekseer3DEffect(enemy_hand_effect_handle, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition().x, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition().y, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition().z);
	}
}

// 手エフェクト停止
void EnemyStateChase::StopHandEffect()
{
	if (enemy_hand_effect_handle >= 0)
	{
		StopEffekseer3DEffect(enemy_hand_effect_handle);
		enemy_hand_effect_handle = -1;
	}
}


void EnemyStateChase::Update()
{

	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), chase_position);

	// プレイヤーに向かって進む方向を単位ベクトルで求める
	VECTOR checkDirection = VNorm(keepDistance);

	// 敵が進む距離（移動速度に基づく）
	VECTOR chaseVector = VScale(checkDirection, MOVE_SPEED);

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
		return EnemyStateKind::STATE_CHASE;
	}
}