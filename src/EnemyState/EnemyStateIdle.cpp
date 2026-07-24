#include "../stdafx.hpp"
#include "EnemyStateIdle.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateIdle::EnemyStateIdle()
{
}

EnemyStateIdle::~EnemyStateIdle()
{
}

EnemyStateKind EnemyStateIdle::GetNextState()
{
    // 待機：基本的に状態維持（必要ならここで次ステート条件を追加する）
    if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
    {
        return EnemyStateKind::STATE_IDLE;
    }

    return EnemyStateKind::STATE_IDLE;
}