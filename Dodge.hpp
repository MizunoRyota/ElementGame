#pragma once
#include "EnemyState.hpp"


class Dodge
{
public:
	Dodge();
	~Dodge();

	VECTOR DodgeEnemy(VECTOR& position, VECTOR& dir, EnemyState& state); // 回避ベクトル適用
	bool GetIsDodgeEnd(); // 回避完了か

private:
	static constexpr float DODGE_TIMER = 60.0f; // 回避継続フレーム
	static constexpr float DODGE_SPEED = 0.2f;  // 回避移動速度

	float dodge_time; // 経過フレーム
};

