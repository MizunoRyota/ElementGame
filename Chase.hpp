#pragma once

// 追跡/レンジ判定
class Chase
{
public:
	Chase();
	~Chase();

	bool RangeWithin(const VECTOR& enemypos, const VECTOR& targetpos); // 追跡レンジ内か

private:
	static constexpr float CHASE_RANGE = 8.0f; // 追跡開始距離
};
