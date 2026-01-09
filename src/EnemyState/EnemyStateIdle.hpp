#pragma once
#include "../EnemyStateBase.hpp"

class EnemyStateIdle : public EnemyStateBase
{
public:
	EnemyStateIdle();
	~EnemyStateIdle();


	void Enter() override {};

	void Update() override {};

	void Exit() override {};

	EnemyStateKind GetNextState()override ;

private:

};
