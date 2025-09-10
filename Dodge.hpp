#pragma once
#include "EnemyState.hpp"


class Dodge
{
public:
	Dodge();
	~Dodge();

	VECTOR DodgeEnemy(VECTOR& position, VECTOR& dir,EnemyState& state);

	bool GetIsDodgeEnd();

private:
	static constexpr 	float DODGE_TIMER = 60.0f; // クールタイム秒数
	static constexpr 	float DODGE_SPEED = 0.125f; // クールタイム秒数


	float dodge_time;

};

