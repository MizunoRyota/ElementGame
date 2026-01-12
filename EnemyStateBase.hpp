#pragma once
#include "IState.hpp"
#include "EnemyStateKind.hpp"
#include "EffectCreator.hpp" // エフェクト生成

class EnemyStateBase : public IState
{
public:
	EnemyStateBase();
	~EnemyStateBase();

	void StartHandEffectForAttack();

	void StopHandEffect();

	void UpdateEffectHandle();

	void ChoseAttackState();

	virtual EnemyStateKind GetNextState()abstract;

protected:
	EffectCreator::EffectType MapEffectTypeForAttack() const; // 攻撃ステートに応じたエフェクト種別へ変換
	static void SetEnemyAttackState(EnemyStateKind state)
	{
		enemy_attack_state = state;
	}
	static EnemyStateKind GetEnemyAttackState()
	{
		return enemy_attack_state;
	}

	int enemy_hand_effect_handle;
	static EnemyStateKind enemy_attack_state;
};
