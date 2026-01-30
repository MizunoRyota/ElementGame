#include "stdafx.hpp"
#include "EnemyStateBase.hpp"
#include "ObjectAccessor.hpp"
// 静的メンバ定義
EnemyStateKind EnemyStateBase::enemy_attack_state = EnemyStateKind::STATE_FIREATTACK;
bool EnemyStateBase::enemy_ondamege_phase2 = false;
bool EnemyStateBase::enemy_ondamege_phase3 = false;
bool EnemyStateBase::enemy_first_specialattack = false;

EnemyStateBase::EnemyStateBase()
	:enemy_hand_effect_handle(-1)
{
	EnemyStateBase::enemy_attack_state = EnemyStateKind::STATE_FIREATTACK;
	EnemyStateBase::enemy_ondamege_phase2 = false;
	EnemyStateBase::enemy_ondamege_phase3 = false;
	EnemyStateBase::enemy_first_specialattack = false;
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
	else if (enemy_attack_state == EnemyStateKind::STATE_JUMPATTACK)
	{
		return EffectCreator::EffectType::JumpAttack;		// 風
	}
	else
	{
		return EffectCreator::EffectType::BulletSpecial;	// 特殊
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

EnemyStateKind EnemyStateBase::ChangeStateOnDamage()
{
	float hpRaito = static_cast<float>(ObjectAccessor::GetObjectAccessor().GetEnemyHp()) / static_cast<float>(ObjectAccessor::GetObjectAccessor().GetEnemyMaxHp());

	if (hpRaito <= ENEMY_HP_PHASE3_RAITO && !enemy_ondamege_phase3)
	{
		enemy_ondamege_phase3 = true;
		return EnemyStateKind::STATE_ONDAMAGE;
	}
	else if (hpRaito <= ENEMY_HP_PHASE2_RAITO && !enemy_ondamege_phase2)
	{
		enemy_ondamege_phase2 = true;
		return EnemyStateKind::STATE_ONDAMAGE;
	}

	return ObjectAccessor::GetObjectAccessor().GetEnemyStateKind();

}