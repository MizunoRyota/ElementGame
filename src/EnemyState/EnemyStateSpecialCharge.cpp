#include "../stdafx.hpp"
#include "EnemyStateSpecialCharge.hpp"
#include "../ObjectAccessor.hpp"
#include "../src/Sounds/SoundManager.hpp"

EnemyStateSpecialCharge::EnemyStateSpecialCharge()
{
    // Enter でリセット
    specialattack_charge_time = 0;
}

EnemyStateSpecialCharge::~EnemyStateSpecialCharge()
{
}

void EnemyStateSpecialCharge::Enter()
{
    // チャージ中の見た目：バリア + チャージエフェクトをループ表示
    EffectCreator::GetEffectCreator().PlayLoop(
        EffectCreator::EffectType::Barrior,
        ObjectAccessor::GetObjectAccessor().GetEnemyPosition());

    EffectCreator::GetEffectCreator().PlayLoop(
        EffectCreator::EffectType::EnemyCharge,
        ObjectAccessor::GetObjectAccessor().GetEnemyPosition());

    // チャージ時間リセット
    specialattack_charge_time = SPECIALATTACK_CHARGE_TIME;

    // SE 再生
    SoundManager::GetSoundManager().PlayChargeSpecialSe();
}

void EnemyStateSpecialCharge::Update()
{
    // 時間経過
    specialattack_charge_time -= SPECIALATTACK_CHARGE_DECREACENUM;

    // ループ演出を敵位置へ追従
    EffectCreator::GetEffectCreator().SetLoopPosition(
        EffectCreator::EffectType::Barrior,
        ObjectAccessor::GetObjectAccessor().GetEnemyPosition());

    EffectCreator::GetEffectCreator().SetLoopPosition(
        EffectCreator::EffectType::EnemyCharge,
        ObjectAccessor::GetObjectAccessor().GetEnemyPosition());
}

void EnemyStateSpecialCharge::Exit()
{
    // チャージ演出停止
    EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Barrior);
    EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EnemyCharge);
}

EnemyStateKind EnemyStateSpecialCharge::GetNextState()
{
    // 弱点ギミック：チャージ中にクリスタルが壊れたらスタン
    if (ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak())
    {
        return EnemyStateKind::STATE_STUN;
    }

    // チャージ完了で特殊攻撃へ
    if (specialattack_charge_time <= 0)
    {
        return EnemyStateKind::STATE_SPECIALATTACK;
    }

    // それ以外は継続
    return EnemyStateKind::STATE_SPECIAL_CHARGE;
}