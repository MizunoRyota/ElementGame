#include "../stdafx.hpp"
#include "EnemyStateChoseAttack.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateChoseAttack::EnemyStateChoseAttack()
{
	attack_is_chose = false;
}

EnemyStateChoseAttack::~EnemyStateChoseAttack()
{

}

void EnemyStateChoseAttack::Enter()
{
	attack_is_chose = true;
	ChoseAttackState();
}

void EnemyStateChoseAttack::ChoseAttackState()
{
	CheckEnemyPhase();
}

void EnemyStateChoseAttack::CheckEnemyPhase()
{
	float hpRaito = static_cast<float>(ObjectAccessor::GetObjectAccessor().GetEnemyHp()) / static_cast<float>(ObjectAccessor::GetObjectAccessor().GetEnemyMaxHp());

	if (hpRaito <= ENEMY_HP_PHASE3_RAITO)
	{
		ChoseNextAttackPhaseThree();
	}	
	else if (hpRaito <= ENEMY_HP_PHASE2_RAITO)
	{
		ChoseNextAttackPhaseTwo();
	}
	else if (hpRaito <= ENEMY_HP_PHASE1_RAITO)
	{
		ChoseNextAttackPhaseOne();
	}
}

void EnemyStateChoseAttack::ChoseNextAttackPhaseOne()
{

	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
	float checkDistance = VSquareSize(keepDistance); // 距離の二乗

	int nextAttackType = rand() % ATTACK_MAX_RAITO;  // 0?99

	if (checkDistance >= LONG_RANGE)
	{
		// 例：遠距離（0-49:風, 50-79:水, 80-99:火）
		if (nextAttackType < ATTACK_RAITO7)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);   // 0..69
		else if (nextAttackType < ATTACK_RAITO8)    SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);  // 69..89
		else                         SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   // 89..99
	}
	else if (checkDistance >= SHORT_RANGE)
	{
		// 例：中距離（0-39:火, 40-69:水, 70-89:風, 90-99:ジャンプ）
		if (nextAttackType < ATTACK_RAITO8)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);   // 0..69
		else if (nextAttackType < ATTACK_RAITO9)    SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);  // 69..89
		else                         SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   // 89..99
	}
}

void EnemyStateChoseAttack::ChoseNextAttackPhaseTwo()
{
	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
	float checkDistance = VSquareSize(keepDistance); // 距離の二乗

	int nextAttackType = rand() % ATTACK_MAX_RAITO;  // 0?99

	if (checkDistance >= LONG_RANGE)
	{
		// 例：遠距離（0-49:風, 50-79:水, 80-99:火）
		if (nextAttackType < ATTACK_RAITO4)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);   // 0..69
		else if (nextAttackType < ATTACK_RAITO8)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);  // 69..89
		else if (nextAttackType < ATTACK_RAITO9)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);  // 69..89
		else                         SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   // 89..99
	}
	else if (checkDistance >= SHORT_RANGE)
	{
		// 例：中距離（0-39:火, 40-69:水, 70-89:風, 90-99:ジャンプ）
		if (nextAttackType < ATTACK_RAITO8)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);   // 0..69
		else if (nextAttackType < ATTACK_RAITO4)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);  // 69..89
		else if (nextAttackType < ATTACK_RAITO9)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);  // 69..89
		else                         SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   // 89..99
	}
}

void EnemyStateChoseAttack::ChoseNextAttackPhaseThree()
{
	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
	float checkDistance = VSquareSize(keepDistance); // 距離の二乗

	int nextAttackType = rand() % ATTACK_MAX_RAITO;  // 0?99

	if (checkDistance >= LONG_RANGE)
	{
		// 例：遠距離（0-49:風, 50-79:水, 80-99:火）
		if (nextAttackType < ATTACK_RAITO4)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);   // 0..69
		else if (nextAttackType < ATTACK_RAITO2)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);  // 69..89
		else if (nextAttackType < ATTACK_RAITO7)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);  // 69..89
		else                         SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   // 89..99
	}
	else if (checkDistance >= SHORT_RANGE)
	{
		// 例：中距離（0-39:火, 40-69:水, 70-89:風, 90-99:ジャンプ）
		if (nextAttackType < ATTACK_RAITO2)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);   // 0..69
		else if (nextAttackType < ATTACK_RAITO4)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);  // 69..89
		else if (nextAttackType < ATTACK_RAITO7)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);  // 69..89
		else                         SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   // 89..99
	}
}

void EnemyStateChoseAttack::Exit()
{
	attack_is_chose = false;
}

EnemyStateKind EnemyStateChoseAttack::GetNextState()
{
	if (attack_is_chose)
	{
		return EnemyStateKind::STATE_CHARGE;
	}
	else
	{
		return ObjectAccessor::GetObjectAccessor().GetEnemyStateKind();
	}
}