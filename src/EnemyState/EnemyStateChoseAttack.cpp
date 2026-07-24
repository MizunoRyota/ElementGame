#include "../stdafx.hpp"
#include "EnemyStateChoseAttack.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"
#include "../AttackWeightManager.hpp"

EnemyStateChoseAttack::EnemyStateChoseAttack()
{
    attack_is_chose = false;
}

EnemyStateChoseAttack::~EnemyStateChoseAttack()
{
}

void EnemyStateChoseAttack::Enter()
{
    // このステートに入ったら必ず1回、次の攻撃を選択する
    attack_is_chose = true;
    ChoseAttackState();
}

void EnemyStateChoseAttack::ChoseAttackState()
{
    // 現在HP割合と距離から、候補テーブルを切り替えて攻撃を決定
    CheckEnemyPhase();
}

void EnemyStateChoseAttack::CheckEnemyPhase()
{
    // 現在HP割合（0.0～1.0）を算出
    float hpRaito = static_cast<float>(ObjectAccessor::GetObjectAccessor().GetEnemyHp()) /
        static_cast<float>(ObjectAccessor::GetObjectAccessor().GetEnemyMaxHp());

    // プレイヤーとの距離（二乗）を算出
    VECTOR keepDistance = VSub(
        ObjectAccessor::GetObjectAccessor().GetPlayerPosition(),
        ObjectAccessor::GetObjectAccessor().GetEnemyPosition());

    float checkDistance = VSquareSize(keepDistance);

    // HPフェーズで分岐（低HPほど行動が激化/特殊が増える想定）
    if (hpRaito <= ENEMY_HP_PHASE3_RAITO)
    {
        ChoseNextAttackPhaseThree(keepDistance, checkDistance);
    }
    else if (hpRaito <= ENEMY_HP_PHASE2_RAITO)
    {
        ChoseNextAttackPhaseTwo(keepDistance, checkDistance);
    }
    else if (hpRaito <= ENEMY_HP_PHASE1_RAITO)
    {
        ChoseNextAttackPhaseOne(keepDistance, checkDistance);
    }
}

void EnemyStateChoseAttack::ChoseNextAttackPhaseOne(const VECTOR& keepDistance, const float& checkDistance)
{

    // 距離に応じて重みテーブルを切り替える（LongRange/ShortRange）
    if (checkDistance >= LONG_RANGE)
    {
        const auto& weights =
            AttackWeightManager::GetAttackWeightManager().GetWeights("PhaseOne", "LongRange");

        std::discrete_distribution<> dist(weights.begin(), weights.end());
        int result = dist(gen);

        if (result == 0)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
        else if (result == 1)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);
    }
    else if (checkDistance >= SHORT_RANGE)
    {
        const auto& weights =
            AttackWeightManager::GetAttackWeightManager().GetWeights("PhaseOne", "ShortRange");

        std::discrete_distribution<> dist(weights.begin(), weights.end());
        int result = dist(gen);

        if (result == 0)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
        else if (result == 1)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);
    }
}

void EnemyStateChoseAttack::ChoseNextAttackPhaseTwo(const VECTOR& keepDistance, const float& checkDistance)
{;

    // フェーズ2では初回だけ特殊行動（Float → SpecialCharge へ）を強制
    if (!enemy_first_specialattack)
    {
        SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);
        enemy_first_specialattack = true;
        return;
    }

    if (checkDistance >= LONG_RANGE)
    {
        const auto& weights =
            AttackWeightManager::GetAttackWeightManager().GetWeights("PhaseTwo", "LongRange");

        std::discrete_distribution<> dist(weights.begin(), weights.end());
        int result = dist(gen);

        if (result == 0)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
        else if (result == 1)    SetEnemyAttackState(EnemyStateKind::STATE_JUMPATTACK);
        else if (result == 2)    SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);
        else if (result == 3)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);
    }
    else if (checkDistance >= SHORT_RANGE)
    {
        const auto& weights =
            AttackWeightManager::GetAttackWeightManager().GetWeights("PhaseTwo", "ShortRange");

        std::discrete_distribution<> dist(weights.begin(), weights.end());
        int result = dist(gen);

        if (result == 0)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
        else if (result == 1)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);
        else if (result == 2)    SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);
        else if (result == 3)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);
    }
}

void EnemyStateChoseAttack::ChoseNextAttackPhaseThree(const VECTOR& keepDistance, const float& checkDistance)
{

    // フェーズ3（低HP）ではフェーズ2のテーブルを流用している（調整ポイント）
    if (checkDistance >= LONG_RANGE)
    {
        const auto& weights =
            AttackWeightManager::GetAttackWeightManager().GetWeights("PhaseThree", "LongRange");

        std::discrete_distribution<> dist(weights.begin(), weights.end());
        int result = dist(gen);

        if (result == 0)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
        else if (result == 1)    SetEnemyAttackState(EnemyStateKind::STATE_JUMPATTACK);
        else if (result == 2)    SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);
        else if (result == 3)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);
    }
    else if (checkDistance >= SHORT_RANGE)
    {
        const auto& weights =
            AttackWeightManager::GetAttackWeightManager().GetWeights("PhaseThree", "ShortRange");

        std::discrete_distribution<> dist(weights.begin(), weights.end());
        int result = dist(gen);

        if (result == 0)         SetEnemyAttackState(EnemyStateKind::STATE_FIREATTACK);
        else if (result == 1)    SetEnemyAttackState(EnemyStateKind::STATE_WATERATTACK);
        else if (result == 2)    SetEnemyAttackState(EnemyStateKind::STATE_WINDATTACK);
        else if (result == 3)    SetEnemyAttackState(EnemyStateKind::STATE_FLOAT);
    }
}

void EnemyStateChoseAttack::Exit()
{
    // 選択処理は完了
    attack_is_chose = false;
}

EnemyStateKind EnemyStateChoseAttack::GetNextState()
{
    // Enter で選択→次フレームから Charge へ
    if (attack_is_chose)
    {
        return EnemyStateKind::STATE_CHARGE;
    }

    // 選択後は現在の敵ステートを維持（外部で上書きされる想定）
    return ObjectAccessor::GetObjectAccessor().GetEnemyStateKind();
}