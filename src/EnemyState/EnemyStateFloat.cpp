#include "../stdafx.hpp"
#include "EnemyStateFloat.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateFloat::EnemyStateFloat(VECTOR& position)
	:enemy_position(position)
{
}
EnemyStateFloat::~EnemyStateFloat()
{
}

void EnemyStateFloat::Enter()
{
	position_is_origin = false;
}

void EnemyStateFloat::Update()
{
	if (!(enemy_position.x > -ORIGIN_OFFSET && enemy_position.x < ORIGIN_OFFSET) || !(enemy_position.z > -ORIGIN_OFFSET && enemy_position.z < ORIGIN_OFFSET))
	{

		VECTOR keepDistance = VSub(VGet(0,0,0), enemy_position);

		// プレイヤーに向かって進む方向を単位ベクトルで求める
		VECTOR checkDirection = VNorm(keepDistance);

		// 敵が進む距離（移動速度に基づく）
		VECTOR chaseVector = VScale(checkDirection, MOVE_SPEED);

		// 敵の位置を更新
		 enemy_position = VAdd(enemy_position, chaseVector);

         return;
	}

	position_is_origin = true;

}

EnemyStateKind EnemyStateFloat::GetNextState()
{
	if (position_is_origin)
	{
		return EnemyStateKind::STATE_SPECIAL_CHARGE;
	}
	else
	{
		return EnemyStateKind::STATE_FLOAT;
	}
}