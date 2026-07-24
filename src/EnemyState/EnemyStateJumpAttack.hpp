#pragma once
#include "../EnemyStateBase.hpp"
#include "EnemyAttackBase.hpp"

class EnemyAttackBase;

// EnemyStateJumpAttack:
// ジャンプ攻撃ステート。
// - アニメの一定フレームまでプレイヤーへ接近
// - 指定フレームでジャンプ攻撃弾（範囲攻撃など）を発射
// - アニメ終了で `STATE_CHOSEATTACK` へ戻る
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
	static constexpr float JUMP_BULLET_SPEED   = 0.175f; // 発射弾速度
	static constexpr float JUMP_ATTACK_TIMING = 49.0f;  // 弾を撃つアニメフレーム

	// 未使用：将来の距離調整用
	static constexpr float BULLETFIRE_DISTANCE = 1.0f;

	static constexpr float JUMP_MOVE_SPEED = 0.14f; // 接近移動速度

	VECTOR& enemy_position;
};
