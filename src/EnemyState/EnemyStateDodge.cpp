#include "../stdafx.hpp"
#include "EnemyStateDodge.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateDodge::EnemyStateDodge(VECTOR& position)
    :dodge_position(position)
{
}

EnemyStateDodge::~EnemyStateDodge()
{

}

void EnemyStateDodge::Enter()
{
    dodge_time = DODGE_TIMER;
    StartHandEffectForAttack();
}

void EnemyStateDodge::Update()
{

    dodge_time -= DODGE_DECREACE_TIME_SPEED;

    // 方向ベクトルを正規化
    VECTOR forward = VNorm(ObjectAccessor::GetObjectAccessor().GetEnemyDirection());

    // Y軸基準の右方向ベクトル
    VECTOR up = VGet(0.0f, 1.0f, 0.0f);
    VECTOR right = VCross(up, forward);
    right = VNorm(right);

    if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_RUNLEFT)
    {
        dodge_position = VAdd(dodge_position, VScale(right, -DODGE_SPEED));
    }
    else if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_RUNRIGHT)
    {
        dodge_position = VAdd(dodge_position, VScale(right, DODGE_SPEED));
    }

    UpdateEffectHandle();

}

void EnemyStateDodge::Exit()
{
    StopHandEffect();
}

EnemyStateKind EnemyStateDodge::GetNextState()
{
    if (dodge_time <= 0)
    {
        return EnemyStateKind::STATE_CHASE;
    }
    else
    {
        return ChangeStateOnDamage();
    }

    return ObjectAccessor::GetObjectAccessor().GetEnemyStateKind();

}