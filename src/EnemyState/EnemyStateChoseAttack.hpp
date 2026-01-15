#pragma once
#include "../EnemyStateBase.hpp"

class EnemyStateChoseAttack : public EnemyStateBase
{
public:
	EnemyStateChoseAttack();
	~EnemyStateChoseAttack();

	enum class ChoseRaito : int
	{
		PhaseOne = 1,
		PhaseTWO = 2,
		PhaseTHREE = 3,
	};

	void Enter() override;

	void Update() override {};

	void Exit() override ;

	void ChoseAttackState();

	void ChoseNextAttackPhaseOne();

	void ChoseNextAttackPhaseTwo();

	void ChoseNextAttackPhaseThree();

	void CheckEnemyPhase();

	EnemyStateKind GetNextState()override;

private:

	static constexpr float ENEMY_HP_PHASE1_RAITO = 1.0f;
	static constexpr float ENEMY_HP_PHASE2_RAITO = 0.7f;
	static constexpr float ENEMY_HP_PHASE3_RAITO = 0.4f;

	static constexpr float ATTACK_RAITO1 = 9.0f;
	static constexpr float ATTACK_RAITO2 = 19.0f;
	static constexpr float ATTACK_RAITO3 = 29.0f;
	static constexpr float ATTACK_RAITO4 = 39.0f;
	static constexpr float ATTACK_RAITO5 = 49.0f;
	static constexpr float ATTACK_RAITO6 = 59.0f;
	static constexpr float ATTACK_RAITO7 = 69.0f;
	static constexpr float ATTACK_RAITO8 = 79.0f;
	static constexpr float ATTACK_RAITO9 = 89.0f;
	static constexpr float ATTACK_RAITO10 = 99.0f;

	static constexpr float SHORT_RANGE = 100.0f;
	static constexpr float LONG_RANGE = 300.0f;

	static constexpr int ATTACK_MAX_RAITO = 100;

	bool attack_is_chose;

};

