#pragma once

#include "EnemyState.hpp"

// 追跡/レンジ判定
class Chase
{
public:
	Chase();
	~Chase();

	void Inintalize() { chase_range = 0; }

	bool RangeWithin(const VECTOR& enemyPos, const VECTOR& targetPos, const EnemyState& enemyState); // 追跡レンジ内か

	void CheckEnemyState(const EnemyState& enemyState);

private:
	static constexpr float FIRE_RANGE = 5.0f;
	static constexpr float WIND_RANGE = 12.0f;
	static constexpr float WATER_RANGE = 8.0f;
	static constexpr float SPECIAL_RANGE = 8.0f;


	float chase_range; // 追跡開始距離
};
