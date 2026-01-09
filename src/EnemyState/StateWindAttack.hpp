#pragma once
#include "../EnemyStateBase.hpp"
#include "EnemyAttackBase.hpp"


class StateWindAttack : public EnemyStateBase, public EnemyAttackBase
{
public:
	StateWindAttack();
	~StateWindAttack();

	void Enter() override;

	void Update() override;

	void Exit() override {};

	EnemyStateKind GetNextState()override;

private:

	static constexpr float WINDBULLET_SPEED = 0.25f;          // 風(ホーミング)弾 速度
	static constexpr float WINDATTACK_TIMING = 40;             // 風攻撃 予備動作開始(仮)フレーム

};
