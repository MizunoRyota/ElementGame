#include "stdafx.hpp"
#include "EnemyMove.hpp"

EnemyMove::EnemyMove()
{
}

EnemyMove::~EnemyMove()
{
}

VECTOR EnemyMove::MoveToOrigin(const VECTOR& pos)
{
	if (!(pos.x > -ORIGIN_OFFSET && pos.x < ORIGIN_OFFSET) || !(pos.z > -ORIGIN_OFFSET && pos.z < ORIGIN_OFFSET))
	{
		move_isorigin = false;

		VECTOR move_position = MoveToTarget(pos, VGet(0, 0, 0));

		return move_position;

	}

	move_isorigin = true;

	return pos;
}

VECTOR EnemyMove::MoveToSky(const VECTOR& enemypos)
{
	if (!(enemypos.y > TARGETSKY_HIGHT - ORIGIN_OFFSET && enemypos.y < TARGETSKY_HIGHT + ORIGIN_OFFSET))
	{
		move_isorigin = false;
		VECTOR move_position = MoveToTarget(enemypos, VGet(enemypos.x, TARGETSKY_HIGHT, enemypos.z));
		return move_position;
	}
	move_isorigin = true;
	return enemypos;
}

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