#include "stdafx.hpp"
#include "Chase.hpp"
#include "Enemy.hpp"
#include "EnemyState.hpp"

Chase::Chase()
	:chase_range(0)
{}

Chase::~Chase() {}

// ターゲットまでの距離が範囲内か
bool Chase::RangeWithin(const VECTOR& enemyPos, const VECTOR& targetPos,const EnemyState& enemyState)
{
	// 非静的メンバー関数は this ポインタ経由で呼び出す必要があります
	CheckEnemyState(enemyState);

	VECTOR keep_distance = VSub(targetPos, enemyPos);
	float check_distance = VSquareSize(keep_distance); // 距離の二乗
	float range_squared = this->chase_range * this->chase_range;
	return check_distance <= range_squared;
}

void Chase::CheckEnemyState(const EnemyState& enemyState)
{
	switch (enemyState)
	{
	case STATE_FIREATTACK:
		chase_range = FIRE_RANGE;
		break;
	case STATE_WINDATTACK:
		chase_range = WIND_RANGE;
		break;
	case STATE_WATERATTACK:
		chase_range = WATER_RANGE;
		break;
	default:
		break;
	}
}