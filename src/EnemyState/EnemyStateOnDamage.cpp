#include "../stdafx.hpp"
#include "../EffectCreator.hpp"
#include "../Sounds/SoundManager.hpp"
#include "EnemyStateOnDamage.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateOnDamage::EnemyStateOnDamage()
{
}

EnemyStateOnDamage::~EnemyStateOnDamage()
{
}

void EnemyStateOnDamage::Enter()
{
    EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BreakEnemy,
       VAdd( ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), {0.0f, EFFECT_HEIGHT, 0.0f}));

    SoundManager::GetSoundManager().PlayBreakEnemySe();

}

EnemyStateKind EnemyStateOnDamage::GetNextState()
{
    // 被弾アニメが終了したら次の行動選択へ
    if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
    {
        return EnemyStateKind::STATE_CHOSEATTACK;
    }

    // 終了するまでこのステートを維持
    return EnemyStateKind::STATE_ONDAMAGE;
}