#pragma once
#include "../EnemyStateBase.hpp"
#include "EnemyAttackBase.hpp"

class EnemyAttackBase;

class StateFireAttack : public EnemyStateBase , public EnemyAttackBase
{
public:
	StateFireAttack();
	~StateFireAttack();

	void Enter() override;

	void Update() override;

	void Exit() override {};

	EnemyStateKind GetNextState()override;

private:
	static constexpr float FIREBULLET_SPEED = 0.40f;           // ‰Î’e ‘¬“x
	static constexpr float FIREATTACK_TIMING = 30;             // ‰ÎUŒ‚ ”­ËƒtƒŒ[ƒ€
};
