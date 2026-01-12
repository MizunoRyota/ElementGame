#pragma once
#include "../EnemyStateBase.hpp"

class EnemyStateDodge : public EnemyStateBase
{
public:
	EnemyStateDodge(VECTOR& position);
	~EnemyStateDodge();

	void Enter() override ;

	void Update() override ;

	void Exit() override ;

	EnemyStateKind GetNextState()override;

private:

	static constexpr float DODGE_TIMER = 60.0f; // 回避行動の持続フレーム
	static constexpr float DODGE_SPEED = 0.2f;  // 回避速度
	static constexpr float DODGE_DECREACE_TIME_SPEED = 0.5f;  // 回避速度

	float dodge_time; // 経過フレーム
	VECTOR& dodge_position;

};
