#pragma once
#include "EnemyState.hpp"

// 敵の回避（ステップ回避）ロジック
class Dodge
{
public:
	Dodge();
	~Dodge();

	VECTOR DodgeEnemy(VECTOR& position, VECTOR& dir, EnemyState& state); // 回避ベクトルを適用
	bool GetIsDodgeEnd(); // 回避行動が終了したか

private:
	static constexpr float DODGE_TIMER = 60.0f; // 回避行動の持続フレーム
	static constexpr float DODGE_SPEED = 0.2f;  // 回避速度

	float dodge_time; // 経過フレーム
};

