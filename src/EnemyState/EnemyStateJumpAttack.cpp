#include "../stdafx.hpp"
#include "EnemyStateJumpAttack.hpp"
#include "../BulletFire.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateJumpAttack::EnemyStateJumpAttack(VECTOR& pos)
	: enemy_position(pos)
{
}

EnemyStateJumpAttack::~EnemyStateJumpAttack()
{
}

void EnemyStateJumpAttack::Update()
{
	// 指定フレームまではプレイヤーへ向かって接近（攻撃の射程調整）
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimationFrame() <= JUMP_ATTACK_TIMING)
	{
		VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), enemy_position);
		VECTOR checkDirection = VNorm(keepDistance);

		VECTOR chaseVector = VScale(checkDirection, JUMP_MOVE_SPEED);
		enemy_position = VAdd(enemy_position, chaseVector);
	}

	// 指定フレームで攻撃を発射
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimationFrame() == JUMP_ATTACK_TIMING)
	{
		enemy_bullet->FireJumpAttack(
			ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition(),
			ObjectAccessor::GetObjectAccessor().GetEnemyDirection(),
			JUMP_BULLET_SPEED);
	}
}

EnemyStateKind EnemyStateJumpAttack::GetNextState()
{
	// アニメが終わったら次の攻撃選択へ
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		return EnemyStateKind::STATE_CHOSEATTACK;
	}

	return EnemyStateKind::STATE_JUMPATTACK;
}