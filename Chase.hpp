#pragma once

class Chase
{
public:
	Chase();
	~Chase();

	bool RangeWithin(const VECTOR& enemypos, const VECTOR& targetpos);

private:
	
	static constexpr float CHASE_RANGE = 15.0f;	//アニメーションを進める速度

};
