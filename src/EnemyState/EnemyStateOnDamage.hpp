#pragma once

#include "../EnemyStateBase.hpp"

class EnemyStateOnDamage : public EnemyStateBase
{
public:
	EnemyStateOnDamage();
	~EnemyStateOnDamage();

	void Enter() override {};

	void Update() override {};

	void Exit() override {};

	EnemyStateKind GetNextState()override;


private:

};
