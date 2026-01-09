#pragma once
#include "../EnemyStateBase.hpp"
#include "EnemyAttackBase.hpp"

class EnemyAttackBase;

class StateWaterAttack : public EnemyStateBase, public EnemyAttackBase
{
public:
	StateWaterAttack();
	~StateWaterAttack();

	void Enter() override;

	void Update() override;

	void Exit() override {};

	EnemyStateKind GetNextState()override;

private:

	static constexpr float WATERBULLET_SPEED = 0.20f;          // …’e ‘¬“x
	static constexpr float WATERATTACK_TIMING = 20;            // …UŒ‚ ”­ËƒtƒŒ[ƒ€

};

