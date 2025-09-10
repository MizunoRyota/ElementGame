#include "stdafx.hpp"
#include "Chase.hpp"

Chase::Chase()
{
}

Chase::~Chase()
{
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