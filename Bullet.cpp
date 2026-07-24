#include "stdafx.hpp"
#include "Pallet.hpp"
#include "Bullet.hpp"
#include "EffectCreator.hpp" // 追従エフェクト用
#include "ObjectAccessor.hpp"

Bullet::Bullet()
{
    // 生成直後はプール内の未使用弾として扱うため非アクティブ開始
    bullet_is_active = false;
}

Bullet::~Bullet() {}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
/// <param name="effectTypeIndex"></param>
void Bullet::Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed, int effectTypeIndex)
{
    // 使い回し（弾プール）前提：前回生成時の追従エフェクトが残っていれば停止してから再初期化する
    if (bullet_trail_handle >= 0)
    {
        StopEffekseer3DEffect(bullet_trail_handle);
        bullet_trail_handle = -1;
    }

    // 初期位置
    bullet_position = pos;

    // 進行方向ベクトルを正規化して保持（実速度は別途 `bullet_speed` で管理）
    bullet_rawdirection = VNorm(dir);

    // 1フレームあたりの移動量ベクトル（方向 * 速度）
    bullet_direction = VScale(bullet_rawdirection, speed);

    // 速度と寿命をリセット
    bullet_speed = speed;
    bullet_life = BULLET_LIFE;

    // 追尾関連は通常弾では無効化しておく
    bullet_is_Homing = false;
    bullet_homingTime = 0.0f;
    bullet_target_getter = nullptr;

    // 弾種（エフェクト種別）を保持し、弾の当たり半径にも反映する
    bullet_effect_type_index = effectTypeIndex;

    InitializeBulletRadius(effectTypeIndex);
    ChangeActiveTrue();

    // 弾に追従するエフェクトを再生（種類未指定の場合は汎用トレイルにフォールバック）
    if (bullet_effect_type_index >= 0)
    {
        bullet_trail_handle = EffectCreator::GetEffectCreator().PlayReturn(
            static_cast<EffectCreator::EffectType>(bullet_effect_type_index),
            bullet_position);
    }
    else
    {
        bullet_trail_handle = EffectCreator::GetEffectCreator().PlayReturn(
            EffectCreator::EffectType::BulletWind,
            bullet_position);
    }
}

/// <summary>
/// ホーミング弾の初期化
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
/// <param name="targetGetter"></param>
/// <param name="homingDuration"></param>
/// <param name="turnSpeedRad"></param>
/// <param name="effectTypeIndex"></param>
void Bullet::InitializeHoming(const VECTOR& pos, const VECTOR& dir, const float& speed,
    std::function<VECTOR()> targetGetter, float homingDuration, float turnSpeedRad, int effectTypeIndex)
{
    // 通常弾の初期化を流用した上で、追尾に必要なパラメータだけ上書きする
    Initialize(pos, dir, speed, effectTypeIndex);

    bullet_is_Homing = true;               // 追尾フラグ
    bullet_homingTime = homingDuration;    // 追尾継続フレーム（または時間として扱う想定）
    bullet_turnSpeed = turnSpeedRad;       // 1更新あたりの最大旋回角（ラジアン）
    bullet_target_getter = std::move(targetGetter); // ターゲット座標取得関数（ロックオン対象切替に対応）
}

/// <summary>
/// エフェクトタイプインデックスに基づいて弾の当たり判定半径を初期化
/// </summary>
/// <param name="effectTypeIndex">エフェクトの種別を示すインデックス。EffectCreator::EffectType列挙型の整数値として使用</param>
void Bullet::InitializeBulletRadius(int effectTypeIndex)
{
    // エフェクト種別＝弾種として、当たり判定半径を切り替える
    switch (effectTypeIndex)
    {
    case (static_cast<int>(EffectCreator::EffectType::BulletFire)):
        bullet_radius = BULLET_FIRE_RADIUS; break;
    case (static_cast<int>(EffectCreator::EffectType::BulletWater)):
        bullet_radius = BULLET_DIFFUSION_RADIUS; break;
    case (static_cast<int>(EffectCreator::EffectType::BulletWind)):
        bullet_radius = BULLET_HOMING_RADIUS; break;
    case (static_cast<int>(EffectCreator::EffectType::BulletSpecial)):
        bullet_radius = BULLET_SPECIAL_RADIUS; break;
    case (static_cast<int>(EffectCreator::EffectType::JumpAttack)):
        bullet_radius = BULLET_JUMPATTACK_RADIUS; break;
    case (static_cast<int>(EffectCreator::EffectType::BulletPlayer)):
        bullet_radius = BULLET_PLAYER_RADIUS; break;
    default:
        // 未定義の弾種は既定値（呼び出し側で設定済み）を維持
        break;
    }
}


/// <summary>
/// 更新
/// </summary>
void Bullet::Update()
{
    // プール内で未使用の弾は更新しない
    if (!IsActive()) return;

    // 移動（寿命減算/追尾処理を含む）
    Move();

    // 追従エフェクトの位置を弾の現在位置に同期する
    if (bullet_trail_handle >= 0)
    {
        SetPosPlayingEffekseer3DEffect(
            bullet_trail_handle,
            bullet_position.x, bullet_position.y, bullet_position.z);
    }

    // 寿命/着弾などの条件を満たしたら停止（非アクティブ化）する
    StopEffect();
}

/// <summary>
/// エフェクト停止/弾の非アクティブ化条件の判定
/// </summary>
void Bullet::StopEffect()
{
    // スペシャル弾：地面に到達したタイミングで消す（演出/判定の都合で寿命とは別条件）
    if (bullet_effect_type_index == static_cast<int>(EffectCreator::EffectType::BulletSpecial))
    {
        if (bullet_position.y <= 0)
        {
            ChangeActiveFalse();
            ResetPosition();
        }
    }
    else if (bullet_life <= 0 || bullet_position.y <= 0 ||
        ObjectAccessor::GetObjectAccessor().GetEnemyHp() == 0 ||
        ObjectAccessor::GetObjectAccessor().GetPlayerHp() == 0)
    {
        // 通常弾：寿命切れ/地面下/ゲーム終了条件などで消す
        ChangeActiveFalse();
        ResetPosition();
    }
}

/// <summary>
/// `from` から `to` へ、最大 `maxStepRad` だけ回転した方向ベクトルを返す（追尾弾の旋回制限用）
/// </summary>
/// <param name="from"></param>
/// <param name="to"></param>
/// <param name="maxStepRad"></param>
/// <returns></returns>
static VECTOR SlerpDirection(const VECTOR& from, const VECTOR& to, float maxStepRad)
{
    VECTOR From = VNorm(from);                         // 正規化した開始方向
    VECTOR To = VNorm(to);                             // 正規化した終了方向

    // 方向ベクトル同士の角度を求め、旋回可能な範囲だけ補間する
    float dot = VDot(From, To);
    dot = std::clamp(dot, -1.0f, 1.0f);

    float angle = acosf(dot);     // 2方向間の角度
    if (angle < 1e-5f) return To; // ほぼ同方向ならそのまま

    float step = min(maxStepRad, angle);               // 実際に旋回させる角度
    float raito = step / angle;                        // 正規化されたステップ比

    // 球面線形補間（Slerp）
    float sinAngle = sinf(angle);
    float coeff0 = sinf((1.0f - raito) * angle) / sinAngle;
    float coeff1 = sinf(raito * angle) / sinAngle;

    VECTOR out = VAdd(VScale(From, coeff0), VScale(To, coeff1));
    return VNorm(out);
}

/// <summary>
/// 弾の移動処理
/// </summary>
void Bullet::Move()
{
    // フレームごとに寿命を減らす（`BULLET_COUNT` は 1更新あたりの減算量）
    bullet_life -= BULLET_COUNT;

    // 追尾弾：ターゲット方向へ徐々に旋回する
    if (bullet_is_Homing && bullet_target_getter)
    {
        VECTOR targetPos = bullet_target_getter();     // ターゲット座標取得
        VECTOR toTarget = VSub(targetPos, bullet_position); // ターゲット方向ベクトル

        // ターゲットと同一座標付近の場合は正規化が不安定なのでスキップ
        float distSq = VDot(toTarget, toTarget);        // ターゲットまでの距離の2乗
        if (distSq > 1e-6f)
        {
            VECTOR desiredDir = VNorm(toTarget);        // 目標方向（正規化）
            bullet_rawdirection = SlerpDirection(bullet_rawdirection, desiredDir, bullet_turnSpeed);
        }

        // 追尾時間の残りが尽きたら通常弾に戻す
        if (bullet_homingTime > 0.0f)
        {
            bullet_homingTime -= 1.0f;
        }
        else
        {
            bullet_is_Homing = false;
        }
    }

    // 現在の生方向と速度から移動ベクトルを作って位置に反映
    bullet_direction = VScale(bullet_rawdirection, bullet_speed);
    bullet_position = VAdd(bullet_position, bullet_direction);
}

/// <summary>
/// 使用状態を非アクティブに変更する（停止処理）
/// </summary>
void Bullet::ChangeActiveFalse()
{
    // 弾を停止し、追尾状態やターゲット参照をリセットする
    bullet_is_active = false;
    bullet_is_Homing = false;
    bullet_target_getter = nullptr;

    // 追従エフェクトも同時に停止（エフェクトのリーク/残留防止）
    if (bullet_trail_handle >= 0)
    {
        StopEffekseer3DEffect(bullet_trail_handle);
        bullet_trail_handle = -1;
    }
}

/// <summary>
/// 使用状態をアクティブに変更する（再利用/発射処理）
/// </summary>
void Bullet::ChangeActiveTrue()
{
    // プールから取り出して使用可能状態にする
    bullet_is_active = true;
}

/// <summary>
/// ポジションを原点にリセットする（非アクティブ化時の退避処理）
/// </summary>
void Bullet::ResetPosition()
{
    // 非アクティブ弾を原点に退避（デバッグ描画や広域判定の影響を避ける目的）
    bullet_position = VGet(0, 0, 0);
}

/// <summary>
/// 描画
/// </summary>
void Bullet::Draw()
{
    // 必要なら当たり判定の可視化に利用する
    //DrawSphere3D(bullet_position, bullet_radius, 10, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);

    // 影（または簡易インジケータ）としてコーンを描画する
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

    // スペシャル弾のみ色を変えて区別する
    if (bullet_radius == BULLET_SPECIAL_RADIUS)
    {
        DrawCone3D(
            VGet(bullet_position.x, SHADOW_TOP_HEIGHT, bullet_position.z),
            VGet(bullet_position.x, SHADOW_BOTTOM_HEIGHT, bullet_position.z),
            bullet_radius,
            SHADOW_DIV,
            Pallet::Red.GetHandle(), Pallet::Red.GetHandle(),
            true);
    }
    else
    {
        DrawCone3D(
            VGet(bullet_position.x, SHADOW_TOP_HEIGHT, bullet_position.z),
            VGet(bullet_position.x, SHADOW_BOTTOM_HEIGHT, bullet_position.z),
            bullet_radius,
            SHADOW_DIV,
            Pallet::Black.GetHandle(), Pallet::Black.GetHandle(),
            true);
    }

    // 描画ブレンドモードを元に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}