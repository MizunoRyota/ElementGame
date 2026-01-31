#pragma once
#include "../EnemyStateBase.hpp"
#include "EnemyAttackBase.hpp"

class EnemyAttackBase;

class EnemyStateJumpAttack : public EnemyStateBase, public EnemyAttackBase
{
public:
	EnemyStateJumpAttack(VECTOR& pos);
	~EnemyStateJumpAttack();

	void Enter() override {};

	void Update() override;

	void Exit() override {};

	EnemyStateKind GetNextState()override;

private:
	static constexpr float JUMP_BULLET_SPEED = 0.30f;        // 火弾 速度
	static constexpr float JUMP_ATTACK_TIMING = 49.0f;       // 火攻撃 発射フレーム
	static constexpr float BULLETFIRE_DISTANCE = 1.0f;       // 火攻撃 発射フレーム
	static constexpr float JUMP_MOVE_SPEED = 0.085f;         // 火弾 速度

	VECTOR& enemy_position;
};
