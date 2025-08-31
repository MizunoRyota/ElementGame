#include "stdafx.hpp"
#include "Chase.hpp"

Chase::Chase()
{
}

Chase::~Chase()
{
}

bool Chase::Update(const VECTOR& enemypos, const VECTOR& targetpos)
{

	bool chase_isend = RangeWithin(enemypos, targetpos);

	return chase_isend;
}

VECTOR Chase::MoveToTarget(const VECTOR& enemypos, const VECTOR& targetpos)
{

	VECTOR keep_distance = VSub(targetpos, enemypos);

	// プレイヤーに向かって進む方向を単位ベクトルで求める
	VECTOR check_direction = VNorm(keep_distance);

	// 敵が進む距離（移動速度に基づく）
	VECTOR chase_vector = VScale(check_direction, CHASE_SPEED);

	// 敵の位置を更新
	VECTOR chase_targetpos = VAdd(enemypos, chase_vector);

	return chase_targetpos;

}

bool Chase::RangeWithin(const VECTOR& enemypos, const VECTOR& targetpos)
{
	//プレイヤーとEnemyの距離の合計を獲得
	VECTOR keep_distance = VSub(targetpos, enemypos);

	//ベクトルを2乗
	float check_distance = VSquareSize(keep_distance);

	//LengthよりDistanceちいさくなったとき返す
	return check_distance <= (CHASE_RANGE * CHASE_RANGE);
}