#include "../stdafx.hpp"
#include "EnemyStateStun.hpp"
#include "../EnemyStateBase.hpp"
#include "../EffectCreator.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateStun::EnemyStateStun()
{
    // スタン残り時間（Enter で毎回リセットする）
    stun_time = 0;
}

EnemyStateStun::~EnemyStateStun()
{
}

void EnemyStateStun::Enter()
{
    // スタン開始：一定時間だけ行動不能にする
    stun_time = STUN_TIME;

    // 頭上付近にスタン演出（ループエフェクト）を開始
    EffectCreator::GetEffectCreator().PlayLoop(
        EffectCreator::EffectType::EnemyStun,
        VAdd(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), VGet(0, STUN_HEIGHT, 0)));
}

void EnemyStateStun::Update()
{
    // スタン時間を減らす（フレームベースの減算）
    stun_time -= STUN_DECREASE_TIME;

    // スタン演出を敵の位置に追従させる（移動/ノックバックしても頭上に出るようにする）
    EffectCreator::GetEffectCreator().SetLoopPosition(
        EffectCreator::EffectType::EnemyStun,
        VAdd(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), VGet(0, STUN_HEIGHT, 0)));
}

void EnemyStateStun::Exit()
{
    // スタン終了：ループエフェクト停止
    EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EnemyStun);
}

EnemyStateKind EnemyStateStun::GetNextState()
{
    // スタンが解けたら次の行動選択へ
    if (stun_time <= 0)
    {
        return EnemyStateKind::STATE_CHOSEATTACK;
    }

    // 被弾などの割り込みで別ステートに遷移する可能性があるため共通処理へ委譲
    return ChangeStateOnDamage();
}