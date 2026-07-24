#pragma once
#include "../EnemyStateBase.hpp"

// EnemyStateCharge:
// 攻撃選択直後の「溜め/構え」ステート。
// - アニメ終了後に左右回避（`STATE_RUNLEFT/STATE_RUNRIGHT`）へランダム遷移
// - 被弾などの割り込みは `ChangeStateOnDamage()` に委譲
class EnemyStateCharge : public EnemyStateBase
{
public:
	EnemyStateCharge();
	~EnemyStateCharge();

	// 溜め開始（必要なら演出開始などをここに実装）
	void Enter() override ;

	// このステートはアニメ進行任せのため Update は空
	void Update() override {};

	void Exit() override {};

	// アニメ終了で回避へ遷移
	EnemyStateKind GetNextState()override;

private:
	// 未使用：浮遊開始タイミング等、将来拡張用の名残
	static constexpr int ENEMY_FLOAT_TIMING = 75;
};
