#include "stdafx.hpp"
#include "ChoseAttack.hpp"
#include "EnemyState.hpp"
ChoseAttack::ChoseAttack()
{
	chose_fire_count = 0;
	chose_water_count = 0;
	chose_wind_count = 0;
}

ChoseAttack::~ChoseAttack()
{
}

EnemyState ChoseAttack::Chose(const EnemyState& enemyState)
{

	EnemyState nextAttack = STATE_FIREATTACK;

	nextAttack = DecideRange(nextAttack);

	return nextAttack;
}

EnemyState ChoseAttack::DecideRange(EnemyState enemyState)
{
	if (chose_fire_count ==  chose_wind_count && chose_water_count == chose_wind_count)
	{
		enemyState = STATE_FIREATTACK;
		chose_fire_count++;
		return enemyState;
	}
	if (chose_fire_count > chose_water_count  && chose_fire_count > chose_wind_count )
	{
		enemyState = STATE_WATERATTACK;
		chose_water_count++;
		return enemyState;
	}
	if (chose_water_count > chose_wind_count && chose_water_count == chose_fire_count)
	{
		enemyState = STATE_WINDATTACK;
		chose_wind_count++;
		return enemyState;
	}

	return enemyState;
}