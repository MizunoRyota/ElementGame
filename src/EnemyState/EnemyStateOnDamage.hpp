#pragma once

#include "../EnemyStateBase.hpp"

// EnemyStateOnDamage:
// 被弾時のリアクション（のけぞり等）を行うステート。
// - ここではアニメの終了を待ってから `STATE_CHOSEATTACK` に戻す
class EnemyStateOnDamage : public EnemyStateBase
{
public:
	EnemyStateOnDamage();
	~EnemyStateOnDamage();

	void Enter() override;

	void Update() override {};

	void Exit() override {};

	EnemyStateKind GetNextState()override;


private:
	static constexpr float EFFECT_HEIGHT = 2.0f; // 被弾effectの高さ
};
