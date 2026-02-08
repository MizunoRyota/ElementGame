#pragma once
#include "../EnemyStateBase.hpp"

class EnemyStateBase;

class EnemyStateSpecialCharge : public EnemyStateBase
{
public:
	EnemyStateSpecialCharge();
	~EnemyStateSpecialCharge();

	void Enter()override;
	void Update()override;
	void Exit()override;
	EnemyStateKind GetNextState()override;

private:
	static constexpr float SPECIALATTACK_CHARGE_TIME = 3000.0f;			// チャージ時間(秒)
	static constexpr float SPECIALATTACK_CHARGE_DECREACENUM = 3.75f;	// チャージ速度

	float specialattack_charge_time;
};
