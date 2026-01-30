#pragma once
#include "../EnemyStateBase.hpp"
#include "EnemyAttackBase.hpp"

class EnemyAttackBase;

class EnemyStateJumpAttack : public EnemyStateBase, public EnemyAttackBase
{
public:
	EnemyStateJumpAttack(VECTOR& pos);
	~EnemyStateJumpAttack();

	void Enter() override {};

	void Update() override;

	void Exit() override {};

	EnemyStateKind GetNextState()override;

private:
	static constexpr float JUMP_BULLET_SPEED = 0.40f;           // ‰Î’e ‘¬“x
	static constexpr float JUMP_ATTACK_TIMING = 48.0f;             // ‰ÎUŒ‚ ”­ËƒtƒŒ[ƒ€
	static constexpr float JUMP_MOVE_SPEED = 0.085f;           // ‰Î’e ‘¬“x

	VECTOR& enemy_position;
};
