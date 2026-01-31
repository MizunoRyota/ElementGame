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
		// 例：遠距離（0-29:火, 30-79:水, 80-99:風）
		if (nextAttackType < ATTACK_RAITO1)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);  
		else if (nextAttackType < ATTACK_RAITO9)    SetEnemyAttackState(EnemyStateKind::STATE_JUMPATTACK);  
		else										SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);   
	}
	else if (checkDistance >= SHORT_RANGE)
	{
		// 例：中距離（30-79:火, 0-29:水, 70-89:風, 80-99:ジャンプ）
		if (nextAttackType < ATTACK_RAITO8)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
		else if (nextAttackType < ATTACK_RAITO3)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);  
		else										SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);
	}
}

void EnemyStateChoseAttack::ChoseNextAttackPhaseTwo()
{
	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
	float checkDistance = VSquareSize(keepDistance); // 距離の二乗

	int nextAttackType = rand() % ATTACK_MAX_RAITO;  // 0?99

	if (!enemy_first_specialattack)
	{
		SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);
		enemy_first_specialattack = true;
		return;
	}

	if (checkDistance >= LONG_RANGE)
	{
		// 例：遠距離（0-39:火, 40-79:水, 80-89:風, 90-99:必殺）
		if (nextAttackType < ATTACK_RAITO4)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
		else if (nextAttackType < ATTACK_RAITO8)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK); 
		else if (nextAttackType < ATTACK_RAITO9)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);		 
		else										SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK); 
	}
	else if (checkDistance >= SHORT_RANGE)
	{
		// 例：中距離（40-79:火, 0-39:水, 80-89:風, 90-99:必殺）
		if (nextAttackType < ATTACK_RAITO8)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK); 
		else if (nextAttackType < ATTACK_RAITO4)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);  
		else if (nextAttackType < ATTACK_RAITO9)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);		
		else										SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK); 
	}
}

void EnemyStateChoseAttack::ChoseNextAttackPhaseThree()
{
	VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
	float checkDistance = VSquareSize(keepDistance); // 距離の二乗

	int nextAttackType = rand() % ATTACK_MAX_RAITO;  // 0?99

	if (checkDistance >= LONG_RANGE)
	{
		// 例：遠距離（0-29:火, 30-49:水, 70-99:風, 50-69:必殺）
		if (nextAttackType < ATTACK_RAITO3)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK); 
		else if (nextAttackType < ATTACK_RAITO5)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);
		else if (nextAttackType < ATTACK_RAITO7)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);		
		else										SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK); 
	}
	else if (checkDistance >= SHORT_RANGE)
	{
		// 例：中距離（30-49:火, 0-29:水, 70-99:風, 50-69:必殺）
		if (nextAttackType < ATTACK_RAITO5)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
		else if (nextAttackType < ATTACK_RAITO5)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);
		else if (nextAttackType < ATTACK_RAITO7)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);
		else										SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);
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

	return ChangeStateOnDamage();

}