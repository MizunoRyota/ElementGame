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

	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimationFrame() <= JUMP_ATTACK_TIMING)
	{
		VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), enemy_position);

		// プレイヤーに向かって進む方向を単位ベクトルで求める
		VECTOR checkDirection = VNorm(keepDistance);

		// 敵が進む距離（移動速度に基づく）
		VECTOR chaseVector = VScale(checkDirection, JUMP_MOVE_SPEED);

		// 敵の位置を更新
		enemy_position = VAdd(enemy_position, chaseVector);
	}

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
	if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
	{
		return EnemyStateKind::STATE_CHOSEATTACK;
	}

	return EnemyStateKind::STATE_JUMPATTACK;
}