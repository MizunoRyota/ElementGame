#pragma once
#include "EnemyState.hpp"

/// @brief UŒ‚•û–@‚Ì‘I‘ğ
class ChoseAttack
{
public:
	ChoseAttack();
	~ChoseAttack();

	EnemyState Chose(const EnemyState& enemyState);

	EnemyState DecideRange(EnemyState enemyState);



private:

	static constexpr float FIRE_RANGE = 5.0f;
	static constexpr float WIND_RANGE = 15.0f;
	static constexpr float WATER_RANGE = 8.0f;
	static constexpr float SPECIAL_RANGE = 8.0f;

	int chose_fire_count;
	int chose_water_count;
	int chose_wind_count;


};
