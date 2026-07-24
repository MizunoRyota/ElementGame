#include "../stdafx.hpp"
#include "EnemyStateFloat.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateFloat::EnemyStateFloat(VECTOR& position)
	: enemy_position(position)
{
}

EnemyStateFloat::~EnemyStateFloat()
{
}

void EnemyStateFloat::Enter()
{
	// 原点復帰開始
	position_is_origin = false;
}

void EnemyStateFloat::Update()
{
	// 原点到達判定：X/Z が許容範囲内に入ったら到達とみなす
	const bool inX = (enemy_position.x > -ORIGIN_OFFSET && enemy_position.x < ORIGIN_OFFSET);
	const bool inZ = (enemy_position.z > -ORIGIN_OFFSET && enemy_position.z < ORIGIN_OFFSET);

	if (!(inX && inZ))
	{
		// 原点(0,0,0) - 現在位置 で向かうベクトルを作る
		VECTOR keepDistance = VSub(VGet(0, 0, 0), enemy_position);

		// 原点へ向かう単位ベクトル
		VECTOR checkDirection = VNorm(keepDistance);

		// 速度を掛けて移動量を作る
		VECTOR chaseVector = VScale(checkDirection, MOVE_SPEED);

		// 位置更新
		enemy_position = VAdd(enemy_position, chaseVector);
		return;
	}

	// 到達
	position_is_origin = true;
}

EnemyStateKind EnemyStateFloat::GetNextState()
{
	// 原点に着いたら特殊チャージへ
	if (position_is_origin)
	{
		return EnemyStateKind::STATE_SPECIAL_CHARGE;
	}

	// まだ到達していなければ継続
	return EnemyStateKind::STATE_FLOAT;
}