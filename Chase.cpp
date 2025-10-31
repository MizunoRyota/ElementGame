#include "stdafx.hpp"
#include "Chase.hpp"

Chase::Chase() {}
Chase::~Chase() {}

// ターゲットまでの距離が範囲内か
bool Chase::RangeWithin(const VECTOR& enemypos, const VECTOR& targetpos)
{
	VECTOR keep_distance = VSub(targetpos, enemypos);
	float check_distance = VSquareSize(keep_distance); // 距離の二乗
	return check_distance <= (CHASE_RANGE * CHASE_RANGE);
}