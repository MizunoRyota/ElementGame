#pragma once

class Chase
{
public:
	Chase();
	~Chase();

	bool Update(const VECTOR&enemypos,const VECTOR &targetpos);
	VECTOR MoveToTarget(const VECTOR& enemypos, const VECTOR& targetpos);
	bool RangeWithin();
private:
	static constexpr float Range = 7.0f;	//アニメーションを進める速度
	static constexpr float MoveSpeed = 0.125f;	//アニメーションを進める速度

	VECTOR m_position;
	VECTOR target_position;
	VECTOR m_direction;
	VECTOR keep_distance;	//プレイヤーとの距離を保持するための変数
	VECTOR check_direction;
	VECTOR m_movevector;
	float check_distance;	//プレイヤーとの距離を保持するための変数
	bool ischase_end;
};