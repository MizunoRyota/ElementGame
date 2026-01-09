#pragma once
#include "../EnemyStateBase.hpp"
#include "EnemyAttackBase.hpp"

class EnemyStateBase;

class EnemyStateSpecialAttack  : public EnemyStateBase, public EnemyAttackBase
{
public:
	EnemyStateSpecialAttack();
	~EnemyStateSpecialAttack();
	void Enter()override;
	void Update()override;
	void Exit()override;
	EnemyStateKind GetNextState()override;

private:
	static constexpr float SPECIALBULLET_SPEED = 0.3f;         // 特殊弾(地割れ等) 速度
	static constexpr float SPECIALEATTACK_TIMING = 35;         // 特殊攻撃 発射フレーム

	float specialattack_charge_time;
};