#include "../stdafx.hpp"
#include "EnemyStateChase.hpp"
#include "../EnemyStateBase.hpp"
#include "../ObjectAccessor.hpp"

EnemyStateChase::EnemyStateChase(VECTOR& position)
    : chase_position(position)
    , chase_range(0)
    , enemy_hand_effect_handle(-1)
{
}

EnemyStateChase::~EnemyStateChase()
{
}

void EnemyStateChase::Enter()
{
    // 追跡開始時に、現在の攻撃種別に応じた追跡距離を決定し、
    // 次の攻撃に向けた手元エフェクトを開始する
    ChoseRange();
    StartHandEffectForAttack();
}

void EnemyStateChase::ChoseRange()
{
    // 攻撃状態に応じて「追跡をやめて攻撃へ遷移する距離」を設定する
    if (enemy_attack_state == EnemyStateKind::STATE_FIREATTACK)
    {
        chase_range = FIRE_RANGE;
    }
    else if (enemy_attack_state == EnemyStateKind::STATE_WATERATTACK)
    {
        chase_range = WATER_RANGE;
    }
    else if (enemy_attack_state == EnemyStateKind::STATE_WINDATTACK)
    {
        chase_range = WIND_RANGE;
    }
    else if (enemy_attack_state == EnemyStateKind::STATE_JUMPATTACK)
    {
        chase_range = JUMPATTACK_RANGE;
    }
    else
    {
        // それ以外（特殊など）は既定レンジ
        chase_range = SPECIAL_RANGE;
    }
}

EffectCreator::EffectType EnemyStateChase::MapEffectTypeForAttack(float chase_range) const
{
    // 追跡距離（＝攻撃種別に紐づくレンジ）から、表示する弾/攻撃エフェクト種別を決める
    if (chase_range == FIRE_RANGE)
    {
        return EffectCreator::EffectType::BulletFire;		// 火
    }
    else if (chase_range == WATER_RANGE)
    {
        return EffectCreator::EffectType::BulletWater;		// 水
    }
    else if (chase_range == WIND_RANGE)
    {
        return EffectCreator::EffectType::BulletWind;		// 風
    }
    else if (chase_range == JUMPATTACK_RANGE)
    {
        return EffectCreator::EffectType::JumpAttack;		// ジャンプ攻撃
    }

    return EffectCreator::EffectType::BulletSpecial;	// 特殊
}

void EnemyStateChase::Update()
{
    // プレイヤー位置 - 敵位置 から、プレイヤーへ向かうベクトルを求める
    VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), chase_position);

    // プレイヤーに向かって進む方向を単位ベクトルで求める
    VECTOR checkDirection = VNorm(keepDistance);

    // 敵が進む距離（移動速度に基づく）
    VECTOR chaseVector = VScale(checkDirection, MOVE_SPEED);

    // 追跡は地面上の移動のみ（上下方向は固定）
    chaseVector.y = 0;

    // 敵の位置を更新
    chase_position = VAdd(chase_position, chaseVector);

    // 手元エフェクトなど、追従エフェクトの更新
    UpdateEffectHandle();
}

bool EnemyStateChase::RangeWithin()
{
    // プレイヤーとの距離が `chase_range` 以内なら攻撃へ
    VECTOR keepDistance = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), chase_position);
    float checkDistance = VSquareSize(keepDistance); // 距離の二乗
    float rangeSquared = (chase_range * chase_range);
    return checkDistance <= rangeSquared;
}

void EnemyStateChase::Exit()
{
    // 追跡終了（攻撃遷移直前）に攻撃準備エフェクトを再生し、追従エフェクトを停止
    EffectCreator::GetEffectCreator().Play(
        EffectCreator::EffectType::ReadyAttack,
        ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition());

    StopHandEffect();
}

EnemyStateKind EnemyStateChase::GetNextState()
{
    // 射程内に入ったら選択済み攻撃状態へ
    if (RangeWithin())
    {
        return GetEnemyAttackState();
    }

    // 射程外では被弾割り込みなどを優先
    return ChangeStateOnDamage();
}