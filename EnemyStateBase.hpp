#pragma once
#include "IState.hpp"
#include "EnemyStateKind.hpp"

class EnemyStateBase : public IState
{
public:
	EnemyStateBase();
	~EnemyStateBase();

	virtual EnemyStateKind GetNextState()abstract;

private:
	
};
