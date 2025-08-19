#pragma once
#include "EnemyAttackBase.hpp"

class EnemyAttackManager
{
public:
	EnemyAttackManager(int modlehandle);
	~EnemyAttackManager();

	void GetVectors(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle);

	void InitializeFireAttack();
	void InitializeWaterAttack();
	void InitializeWindAttack();

	VECTOR FireAttack(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle);
	VECTOR WaterAttack(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle);
	VECTOR WindAttack(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle);
	VECTOR JumpAttack(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle);
	bool IsFireAttack();
	bool IsWaterAttack();
	bool IsWindAttack();

	void DebugDraw();
private:
	int model_handle;
	VECTOR player_position ;
	VECTOR enemy_position ;
	VECTOR angle_vector ;
	bool attack_isfire;
	bool attack_iswater;
	bool attack_iswind;

	std::shared_ptr<EnemyAttackBase> water_attack;
	std::shared_ptr<EnemyAttackBase> wind_attack;
	std::shared_ptr<EnemyAttackBase> fire_attack;
	std::vector<std::shared_ptr<EnemyAttackBase>> enemyattack_manager;

};