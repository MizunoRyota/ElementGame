#include "../stdafx.hpp"
#include "EnemyStateCharge.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateCharge::EnemyStateCharge()
{
}

EnemyStateCharge::~EnemyStateCharge()
{
}

void EnemyStateCharge::Enter()
{
    // 溜め開始時に行う処理があればここに追加（現状はアニメ再生のみ想定）
}

EnemyStateKind EnemyStateCharge::GetNextState()
{
    // アニメが終わったら左右どちらかに回避して次行動へ繋げる
    if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
    {
        int enemy_dodgechose = GetRand(1);

        if (enemy_dodgechose == 0)      return EnemyStateKind::STATE_RUNLEFT;
        else if (enemy_dodgechose == 1) return EnemyStateKind::STATE_RUNRIGHT;
    }

    // ダメージを受けた等の割り込み（共通処理）
    return ChangeStateOnDamage();
}
