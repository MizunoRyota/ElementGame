#include "stdafx.hpp"
#include "EnemyStateBase.hpp"
#include "ObjectAccessor.hpp"
// 静的メンバ定義
EnemyStateKind EnemyStateBase::enemy_attack_state = EnemyStateKind::STATE_FIREATTACK;

EnemyStateBase::EnemyStateBase()
	:enemy_hand_effect_handle(-1)
{
}

EnemyStateBase::~EnemyStateBase()
{
}

EffectCreator::EffectType EnemyStateBase::MapEffectTypeForAttack() const
{
	if (enemy_attack_state == EnemyStateKind::STATE_FIREATTACK)
	{
		return EffectCreator::EffectType::BulletFire;		// 火
	}
	else if (enemy_attack_state == EnemyStateKind::STATE_WATERATTACK)
	{
		return EffectCreator::EffectType::BulletWater;		// 水
	}
	else if (enemy_attack_state == EnemyStateKind::STATE_WINDATTACK)
	{
		return EffectCreator::EffectType::BulletWind;		// 風
	}
	else
	{
		return EffectCreator::EffectType::BulletSpecial;	// 特殊
	}
}

void EnemyStateBase::ChoseAttackState()
{

	srand((unsigned)time(NULL));

	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
	float checkDistance = VSquareSize(keepDistance); // 距離の二乗

	int attackType = rand() % 100;  // 0?99

	if (checkDistance >= 400.0f)
	{
		// 例：遠距離（0-49:風, 50-79:水, 80-99:火）
		if (attackType < 50)         SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   // 0..49
		else if (attackType < 80)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);  // 50..79
		else                         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);   // 80..99
	}
	else if (checkDistance >= 200.0f)
	{
		// 例：中距離（0-39:火, 40-69:水, 70-89:風, 90-99:ジャンプ）
		if (attackType < 70)		 SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);  // 40..69
		else if (attackType < 100)    SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   // 70..89
	}
}

void EnemyStateBase::UpdateEffectHandle()
{
	if (enemy_hand_effect_handle >= 0)
	{
		SetPosPlayingEffekseer3DEffect(enemy_hand_effect_handle, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition().x, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition().y, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition().z);
	}
}

// 手エフェクト停止
void EnemyStateBase::StopHandEffect()
{
	if (enemy_hand_effect_handle >= 0)
	{
		StopEffekseer3DEffect(enemy_hand_effect_handle);
		enemy_hand_effect_handle = -1;
	}
}

// 手エフェクトを攻撃に応じて再生
void EnemyStateBase::StartHandEffectForAttack()
{
	// 既に同攻撃のエフェクトが再生中なら何もしない
	if (enemy_hand_effect_handle >= 0) return;

	// いったん停止
	StopHandEffect();

	const auto effType = MapEffectTypeForAttack();
	enemy_hand_effect_handle = EffectCreator::GetEffectCreator().PlayReturn(effType, ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition());
}
