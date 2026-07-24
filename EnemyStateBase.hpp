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

	EnemyStateKind ChangeStateOnDamage();

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

	int enemy_hand_effect_handle; //敵の手のエフェクトハンドル

	static EnemyStateKind enemy_attack_state; //敵のステートの状態

	static bool enemy_ondamege_phase2; //敵のフェーズ2前ののけぞりフラグ
	static bool enemy_ondamege_phase3; //敵のフェーズ3前ののけぞりフラグ
	static bool enemy_first_specialattack; //最初の必殺技フラグ

private:
	static constexpr float ENEMY_HP_PHASE2_RAITO = 0.8f; //フェーズ2へのHP割合
	static constexpr float ENEMY_HP_PHASE3_RAITO = 0.4f; //フェーズ3へのHP割合

};
