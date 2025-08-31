#pragma once

class Chase
{
public:
	Chase();
	~Chase();

	bool Update(const VECTOR& enemypos, const VECTOR& targetpos);

	VECTOR MoveToTarget(const VECTOR& enemypos, const VECTOR& targetpos);

	bool RangeWithin(const VECTOR& enemypos, const VECTOR& targetpos);

private:
	
	static constexpr float CHASE_RANGE = 5.0f;	//アニメーションを進める速度
	static constexpr float CHASE_SPEED = 0.1f;	//アニメーションを進める速度

};
