#include"DxLib.h"
#include "Chase.hpp"

Chase::Chase()
	:m_position(VGet(0, 0, 0))
	, target_position(VGet(0, 0, 0))
	, m_direction(VGet(0,0,0))
	, ischase_end(false)
	,check_direction(VGet(0,0,0))
{
}

Chase::~Chase()
{
}

bool Chase::Update(const VECTOR& enemypos, const VECTOR& targetpos)
{
	this->m_position = enemypos;
	this->target_position = targetpos;

	ischase_end = RangeWithin();

	return ischase_end;
}

VECTOR Chase::MoveToTarget(const VECTOR& enemypos, const VECTOR& targetpos)
{
	this->m_position = enemypos;
	this->target_position = targetpos;


	keep_distance = VSub(target_position, m_position);

	// プレイヤーに向かって進む方向を単位ベクトルで求める
	check_direction = VNorm(keep_distance);

	// 敵が進む距離（移動速度に基づく）
	m_movevector = VScale(check_direction, MoveSpeed);

	// 敵の位置を更新
	m_position = VAdd(m_position, m_movevector);

	return m_position;

}

bool Chase::RangeWithin()
{
	//プレイヤーとEnemyの距離の合計を獲得
	keep_distance = VSub(target_position, m_position);

	//ベクトルを2乗
	check_distance = VSquareSize(keep_distance);
	//LengthよりDistanceちいさくなったとき返す
	return check_distance <= (Range * Range);
}