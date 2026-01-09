#pragma once
#include "../PlayerStateBase.hpp"

class PlayerStateIdle : public PlayerStateBase
{
public:
	PlayerStateIdle();
	~PlayerStateIdle();

	void Enter() override {};

	void Update() override ;

	void Exit() override ;

   PlayerStateKind GetNextState()override;

private:

};
