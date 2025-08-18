#include "Dxlib.h"
#include "EnemyAttackManager.hpp"
#include "EnemyWaterAttack.hpp"
#include "EnemyWindAttack.hpp"
#include "EnemyFireAttack.hpp"

EnemyAttackManager::EnemyAttackManager(int modelhadle)
	:attack_isfire(false)
	, attack_iswater(false)
	, attack_iswind(false)
{
	this->model_handle = modelhadle;
	water_attack = std::make_shared<EnemyWaterAttack>(model_handle);
	wind_attack = std::make_shared<EnemyWindAttack>(model_handle);
	fire_attack = std::make_shared<EnemyFireAttack>(model_handle);
}

EnemyAttackManager::~EnemyAttackManager()
{
}

void EnemyAttackManager::InitializeFireAttack()
{
	fire_attack->Initialize();
}

void EnemyAttackManager::InitializeWaterAttack()
{
	water_attack->Initialize();
}

void EnemyAttackManager::InitializeWindAttack()
{
	wind_attack->Initialize();
}

void EnemyAttackManager::GetVectors(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)
{
	player_position = playerpos;
	enemy_position = enemypos;
	angle_vector = angle;
}

VECTOR EnemyAttackManager::FireAttack(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)
{
	GetVectors(playerpos, enemypos, angle);
	enemy_position = fire_attack->Update(playerpos, enemypos, angle_vector);
	return enemy_position;
}

VECTOR EnemyAttackManager::WaterAttack(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)
{
	GetVectors(playerpos,enemypos,angle);
	enemy_position = water_attack->Update(playerpos, enemypos, angle_vector);
	return enemy_position;
}

VECTOR EnemyAttackManager::WindAttack(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)
{
	GetVectors(playerpos, enemypos, angle);
	enemy_position = wind_attack->Update(playerpos, enemypos, angle_vector);
	return enemy_position;
}

VECTOR EnemyAttackManager::JumpAttack(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)
{
	return enemy_position;
}

bool EnemyAttackManager::IsFireAttack()
{
	return attack_isfire = fire_attack->GetIsAction();
}

bool EnemyAttackManager::IsWaterAttack()
{
	return attack_iswater = water_attack->GetIsAction();
}

bool EnemyAttackManager::IsWindAttack()
{
	return attack_iswind = wind_attack->GetIsAction();
}

void EnemyAttackManager::DebugDraw()
{
	fire_attack->DebugDraw();
	wind_attack->DebugDraw();
	water_attack->DebugDraw();
}
