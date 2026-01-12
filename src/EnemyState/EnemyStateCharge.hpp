#pragma once
#include "../EnemyStateBase.hpp"

class EnemyStateCharge : public EnemyStateBase
{
public:
	EnemyStateCharge();
	~EnemyStateCharge();

	void Enter() override ;

	void Update() override {};

	void Exit() override {};

	EnemyStateKind GetNextState()override;

private:
	static constexpr int ENEMY_FLOAT_TIMING = 75;    // Phase3 à»ç~HP

};
