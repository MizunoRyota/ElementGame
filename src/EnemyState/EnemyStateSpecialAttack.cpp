#include "../stdafx.hpp"
#include "EnemyStateSpecialAttack.hpp"
#include "../BulletFire.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateSpecialAttack::EnemyStateSpecialAttack()
{
}

EnemyStateSpecialAttack::~EnemyStateSpecialAttack()
{
}

void EnemyStateSpecialAttack::Enter()
{
    // 特殊攻撃中はバリア演出を出し続ける
    EffectCreator::GetEffectCreator().PlayLoop(
        EffectCreator::EffectType::Barrior,
        ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
}

void EnemyStateSpecialAttack::Update()
{
    // 指定フレームで咆哮演出 + 特殊弾発射
    if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimationFrame() == SPECIALEATTACK_TIMING)
    {
        EffectCreator::GetEffectCreator().Play(
            EffectCreator::EffectType::Roar,
            ObjectAccessor::GetObjectAccessor().GetEnemyPosition());

        enemy_bullet->FireSpecialAttack(
            ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition(),
            ObjectAccessor::GetObjectAccessor().GetCameraDirection(),
            SPECIALBULLET_SPEED);
    }

    // バリアは敵の位置に追従
    EffectCreator::GetEffectCreator().SetLoopPosition(
        EffectCreator::EffectType::Barrior,
        ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
}

void EnemyStateSpecialAttack::Exit()
{
    // バリア演出停止
    EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Barrior);
}

EnemyStateKind EnemyStateSpecialAttack::GetNextState()
{
    // 攻撃アニメが終了したら次の行動選択へ
    if (ObjectAccessor::GetObjectAccessor().GetEnemyAnimaitonIsEnd())
    {
        return EnemyStateKind::STATE_CHOSEATTACK;
    }

    return EnemyStateKind::STATE_SPECIALATTACK;
}