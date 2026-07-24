#include "stdafx.hpp"
#include "BulletFire.hpp"
#include "GameObject.hpp"
#include "BulletCreator.hpp"
#include "Player.hpp"
#include "EffectCreator.hpp"
#include "src/Sounds/SoundManager.hpp"
#include "ObjectAccessor.hpp"

BulletFire::BulletFire()
{
    bullet_fire_cooltimer = 0; // 発射クール初期化
}

BulletFire::~BulletFire() {}

/// <summary>
/// エフェクト種別への変換
/// </summary>
/// <param name="effect_flavor"></param>
/// <returns></returns>
int BulletFire::ToEffectIndex(EffectFlavor effect_flavor)
{
    using ET = EffectCreator::EffectType;
    switch (effect_flavor)
    {
    case EffectFlavor::BulletFire:return (int)ET::BulletFire;
    case EffectFlavor::BulletWater:return (int)ET::BulletWater;
    case EffectFlavor::BulletWind:return (int)ET::BulletWind;
    case EffectFlavor::BulletSpecial:return (int)ET::BulletSpecial;
    case EffectFlavor::BulletHit:return (int)ET::BulletHit;
    case EffectFlavor::BulletPlayer:return (int)ET::BulletPlayer;
    case EffectFlavor::JumpAttack:return (int)ET::JumpAttack;
    }
    return (int)ET::BulletWind; // 既定
}

/// <summary>
/// 直線状に弾を発射する
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
void BulletFire::FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
    if (bullet_fire_cooltimer > 0) return; // クール中
    BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed, ToEffectIndex(EffectFlavor::BulletFire));
}

/// <summary>
/// プレイヤーの通常攻撃
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
void BulletFire::FirePlayer(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
    if (bullet_fire_cooltimer > 0) return; // クール中
    
    SoundManager::GetSoundManager().PlayFireSe();

    bullet_fire_cooltimer = BULLET_COOLTIME; // クール開始
    BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed, ToEffectIndex(EffectFlavor::BulletPlayer));
}

/// <summary>
/// 拡散弾
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
void BulletFire::FireDiffusion(const VECTOR& pos, const VECTOR& dir, const float& speed)
{

    SoundManager::GetSoundManager().PlayFireSe();

    VECTOR bulletForword = VNorm(dir);                                      // 基準方向
    float bulletRotate = DX_TWO_PI_F / DIFFUSION_RADIUS;                   // 回転角
    bulletForword = BulletRotateHorizontal(bulletForword, -bulletRotate * DIFFUSION_OFFSET); // 初期ずらし
    for (int bullet_num = 0; bullet_num < DIFFUSION_NUM; bullet_num++)
    {
        BulletCreator::GetBulletCreator().CreateBullet(pos, bulletForword, speed, ToEffectIndex(EffectFlavor::BulletWater));
        bulletForword = BulletRotateHorizontal(bulletForword, bulletRotate);
    }
}

/// <summary>
///　ジャンプ攻撃：指定方向を中心に全方位に発射
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
void BulletFire::FireJumpAttack(const VECTOR& pos, const VECTOR& dir, const float& speed)
{

    SoundManager::GetSoundManager().PlayFireSe();

    VECTOR bulletForword = VNorm(dir);                                      // 基準方向

    float bulletRotate = DX_TWO_PI_F / JUMPATTACK_RADIUS;                  // 回転角
    bulletForword = BulletRotateHorizontal(bulletForword, -bulletRotate * JUMPATTACK_OFFSET); // 初期ずらし
    for (int bullet_num = 0; bullet_num < JUMPATTACK_NUM; bullet_num++)
    {
        const VECTOR spawnPos = VAdd(pos, VScale(bulletForword, BULLET_SPAWN_FORWARD_OFFSET)); // 発射位置
        BulletCreator::GetBulletCreator().CreateBullet(spawnPos, bulletForword, speed, ToEffectIndex(EffectFlavor::JumpAttack));
        bulletForword = BulletRotateHorizontal(bulletForword, bulletRotate);
    }
}

/// <summary>
/// ホーミング弾：指定方向を中心に全方位に発射し、一定時間プレイヤーを追尾する
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
void BulletFire::FireHoming(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
    if (homing_remaining_shots > 0) return; // 連射中は再開しない

    SoundManager::GetSoundManager().PlayFireSe();

    homing_remaining_shots = HOMING_SHOT_COUNT;
    homing_interval_timer = 0;
    homing_spawn_pos = pos;
    homing_initial_dir = dir;
    homing_speed = speed;
}

/// <summary>
/// 必殺技：指定方向を中心に複数のリング状に弾を発射し、落下演出も兼ねる
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
void BulletFire::FireSpecialAttack(const VECTOR& pos, const VECTOR& dir, const float& speed)
{

    SoundManager::GetSoundManager().PlayExplosionSe();


    bullet_fire_cooltimer = BULLET_COOLTIME;

    int specialRingNum = 16;                           // 外周弾数
    const VECTOR downDir = VGet(0.0f, -1.0f, 0.0f);   // 下向きベクトル

    for (int ring = 0; ring < INNER_RINGS; ++ring)
    {
        float radius = RING_RADIUS - ring * RADIUS_STEP;
        specialRingNum--; // 内側ほど密に
        if (radius <= 0.0f) continue;
        for (int specialBulletNum = 0; specialBulletNum < specialRingNum; specialBulletNum++)
        {
            float ringRaito = (float)specialBulletNum / specialRingNum;
            float ang = DX_TWO_PI_F * ringRaito;                                  // 角度
            VECTOR offset = VGet(cosf(ang) * radius, DROP_HEIGHT, sinf(ang) * radius); // オフセット位置
            VECTOR spawnPos = VAdd(pos, offset);                                 // 発射位置
            BulletCreator::GetBulletCreator().CreateBullet(spawnPos, downDir, speed, ToEffectIndex(EffectFlavor::BulletSpecial));

            // マーカー表示等を行うならここで groundPos を使用
            VECTOR groundPos = VAdd(pos, VGet(cosf(ang) * radius, 0.0f, sinf(ang) * radius)); // 地面上の位置
        }
    }
}

/// <summary>
/// 弾丸の発射状態を更新
/// </summary>
void BulletFire::FireUpdate()
{
    if (bullet_fire_cooltimer > 0) bullet_fire_cooltimer--;

    if (homing_remaining_shots > 0)
    {
        if (homing_interval_timer <= 0)
        {
            SpawnHomingBullet();
            homing_remaining_shots--;
            homing_interval_timer = HOMING_INTERVAL_FRAMES;
        }
        else
        {
            homing_interval_timer--;
        }
    }
}

/// <summary>
/// 水平方向の回転
/// </summary>
/// <param name="dir"></param>
/// <param name="angle"></param>
/// <returns></returns>
VECTOR BulletFire::BulletRotateHorizontal(const VECTOR& dir, float angle)
{
    float c = cosf(angle); float s = sinf(angle);
    return VGet(dir.x * c - dir.z * s, dir.y, dir.x * s + dir.z * c);
}

/// <summary>
/// ホーミング弾のスポーン処理。プレイヤーの位置を取得するコールバックを渡して生成する
/// </summary>
void BulletFire::SpawnHomingBullet()
{
    VECTOR currentSpawnPos = ObjectAccessor::GetObjectAccessor().GetEnemyHandPosition(); // 敵の発射位置
    VECTOR targetPos = ObjectAccessor::GetObjectAccessor().GetPlayerCapsuleTop();       // プレイヤーのターゲット位置
    VECTOR toTarget = VSub(targetPos, currentSpawnPos);                                  // ターゲット方向ベクトル
    if (VDot(toTarget, toTarget) < 1e-6f)
    {
        toTarget = homing_initial_dir;
    }
    VECTOR dir = VNorm(toTarget);                                                       // 正規化された発射方向

    BulletCreator::GetBulletCreator().CreateHomingBullet(
        currentSpawnPos,
        dir,
        homing_speed,
        [] { return ObjectAccessor::GetObjectAccessor().GetPlayerCapsuleTop(); },
        HOMING_DURATION,
        HOMING_TURN_SPEED,
        ToEffectIndex(EffectFlavor::BulletWind));
}

