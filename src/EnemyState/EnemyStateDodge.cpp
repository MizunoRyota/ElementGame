#include "../stdafx.hpp"
#include "EnemyStateDodge.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateDodge::EnemyStateDodge(VECTOR& position)
    : dodge_position(position)
{
}

EnemyStateDodge::~EnemyStateDodge()
{
}

void EnemyStateDodge::Enter()
{
    // 回避開始：タイマーをセットし、次行動に向けた手元エフェクトを開始
    dodge_time = DODGE_TIMER;
    StartHandEffectForAttack();
}

void EnemyStateDodge::Update()
{
    // 経過時間
    dodge_time -= DODGE_DECREACE_TIME_SPEED;

    // 敵の前方向（正規化）
    VECTOR forward = VNorm(ObjectAccessor::GetObjectAccessor().GetEnemyDirection());

    // up × forward で「右方向」を作る（Y軸上方向を基準化）
    VECTOR up = VGet(0.0f, 1.0f, 0.0f);
    VECTOR right = VCross(up, forward);
    right = VNorm(right);

    // 敵ステートが RUNLEFT/RUNRIGHT のどちらかで左右移動方向を決定する
    if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_RUNLEFT)
    {
        dodge_position = VAdd(dodge_position, VScale(right, -DODGE_SPEED));
    }
    else if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_RUNRIGHT)
    {
        dodge_position = VAdd(dodge_position, VScale(right, DODGE_SPEED));
    }

    // 手元エフェクトの追従更新
    UpdateEffectHandle();
}

void EnemyStateDodge::Exit()
{
    // 回避終了：手元エフェクト停止
    StopHandEffect();
}

EnemyStateKind EnemyStateDodge::GetNextState()
{
    // タイマーが尽きたら追跡へ
    if (dodge_time <= 0)
    {
        return EnemyStateKind::STATE_CHASE;
    }

    // 途中で被弾などの割り込みがあれば共通処理へ
    return ChangeStateOnDamage();
}