#pragma once

class Chase
{
public:
	Chase();
	~Chase();

	bool RangeWithin(const VECTOR& enemypos, const VECTOR& targetpos); // ’ÇÕƒŒƒ“ƒW“à”»’è

private:
	static constexpr float CHASE_RANGE = 8.0f; // ’ÇÕI—¹‹——£
};
