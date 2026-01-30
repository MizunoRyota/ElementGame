#include "stdafx.hpp"
#include "EnemyMove.hpp"

EnemyMove::EnemyMove()
{
}

EnemyMove::~EnemyMove()
{
}

// targetpos に向けて一定速度で接近
VECTOR EnemyMove::MoveToTarget(const VECTOR& enemypos, const VECTOR& targetpos)
{

	VECTOR keep_distance = VSub(targetpos, enemypos);

	// プレイヤーに向かって進む方向を単位ベクトルで求める
	VECTOR check_direction = VNorm(keep_distance);

	// 敵が進む距離（移動速度に基づく）
	VECTOR chase_vector = VScale(check_direction, MOVE_SPEED);

	// 敵の位置を更新
	VECTOR chase_targetpos = VAdd(enemypos, chase_vector);

	return chase_targetpos;

}