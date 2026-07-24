#include "stdafx.hpp"
#include "CollisionSystem.hpp"
#include "SharedData.hpp"
#include "BulletCreator.hpp"
#include "Bullet.hpp"
#include "Collision.hpp"
#include "Enemy.hpp"
#include "PlayerStateKind.hpp"
#include "EnemyStateKind.hpp"
#include "Player.hpp"
#include "Crystal.hpp"
#include "Camera.hpp"
#include "EffectCreator.hpp" 
#include "ObjectAccessor.hpp"

namespace
{

    constexpr int BULLET_DAMAGE_TO_ENEMY    = 1;
    constexpr int BULLET_DAMAGE_TO_CRYSTAL = 1;
    constexpr int BULLET_DAMAGE_TO_PLAYER  = 10;
    constexpr int SEPCIALBULLET_DAMAGE_TO_PLAYER = 30;

    // キャラクター同士の押し戻し（カプセル同士）に使う半径
    constexpr float PLAYER_KNOCKBACK_RADIUS         = 2.0f;
    constexpr float ENEMY_KNOCKBACK_RADIUS          = 2.0f;
    constexpr float ENEMY_SPECIAL_KNOCKBACK_RADIUS  = 5.0f;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="shared"></param>
void CollisionSystem::Resolve(SharedData& shared)
{
    // SharedData から対象オブジェクトを名前で取得
    auto enemy   = std::dynamic_pointer_cast<Enemy>(shared.FindObject("Enemy"));
    auto player  = std::dynamic_pointer_cast<Player>(shared.FindObject("Player"));
    auto crystal = std::dynamic_pointer_cast<Crystal>(shared.FindObject("Crystal"));

    // 弾は BulletCreator の弾プールで一括管理
    auto& bullet_creator = BulletCreator::GetBulletCreator();
    const int count = bullet_creator.GetBulletCount();

    // =================================================================
    // 1) キャラクター同士（Enemy vs Player）の当たり判定
    //    - 敵の状態により当たり判定（半径）を変更
    //    - ヒット時は「めり込み分（最小距離）」だけプレイヤーを押し戻す
    // =================================================================
    if (enemy && player)
    {
        bool hitPlayer = false;

        const auto enemyState = ObjectAccessor::GetObjectAccessor().GetEnemyStateKind();
        const bool isEnemySpecial = (enemyState == EnemyStateKind::STATE_SPECIAL_CHARGE ||
                                    enemyState == EnemyStateKind::STATE_SPECIALATTACK);

        // 特殊中は敵側の当たりを大きくして、体当たり/大技感を強める
        if (isEnemySpecial)
        {
            hitPlayer = Collision::CheckCapsuleCapsuleCollision(
                player->GetPosition(), PLAYER_KNOCKBACK_RADIUS, player->GetCapsuleHeight(),
                enemy->GetPosition(),  ENEMY_SPECIAL_KNOCKBACK_RADIUS, enemy->GetCapsuleHeight());
        }
        else
        {
            hitPlayer = Collision::CheckCapsuleCapsuleCollision(
                player->GetPosition(), PLAYER_KNOCKBACK_RADIUS, player->GetCapsuleHeight(),
                enemy->GetPosition(),  ENEMY_KNOCKBACK_RADIUS, enemy->GetCapsuleHeight());
        }

        if (hitPlayer)
        {
            // 敵→プレイヤー方向へ押し戻すための方向ベクトル
            VECTOR pushDir = VSub(player->GetPosition(), enemy->GetPosition());

            // NOTE: knockbackDistance は現状使用していないが、将来の調整用に残っている
            float knockbackDistance = VSquareSize(pushDir);
            (void)knockbackDistance;

            pushDir = VNorm(pushDir);

            // カプセル同士の「めり込み量」を求め、その分だけプレイヤーを移動させて解決する
            if (isEnemySpecial)
            {
                player->ApplyKnockback(VScale(pushDir, Collision::GetCapsuleCapsuleMinDistance(
                    player->GetPosition(), PLAYER_KNOCKBACK_RADIUS, player->GetCapsuleHeight(),
                    enemy->GetPosition(),  ENEMY_SPECIAL_KNOCKBACK_RADIUS, enemy->GetCapsuleHeight())));
            }
            else
            {
                player->ApplyKnockback(VScale(pushDir, Collision::GetCapsuleCapsuleMinDistance(
                    player->GetPosition(), PLAYER_KNOCKBACK_RADIUS, player->GetCapsuleHeight(),
                    enemy->GetPosition(),  ENEMY_KNOCKBACK_RADIUS, enemy->GetCapsuleHeight())));
            }
        }
    }

    // =================================================================
    // 2) レーザー（プレイヤー状態が LASER のとき） vs 敵
    //    - レーザー発射中は弾の衝突判定を行わず、ここで早期 return
    //    - 判定は「線分（レーザー） vs 線分（敵の被弾線分）」で行う
    // =================================================================
    if (ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() == PlayerStateKind::STATE_LASER)
    {
        bool hitEnemy = Collision::CheckSegmentSegmentColliison(
            ObjectAccessor::GetObjectAccessor().GetEnemyPosition(),
            ObjectAccessor::GetObjectAccessor().GetEnemyGetHitPosition(),
            ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition(),
            ObjectAccessor::GetObjectAccessor().GetLaserEndPosition());

        if (hitEnemy && enemy)
        {
            enemy->TakeDamage(BULLET_DAMAGE_TO_ENEMY);
        }

        // レーザー中は弾（球）判定をスキップ
        return;
    }

    // =================================================================
    // 3) 弾（BulletCreator 管理） vs 各キャラクター
    //    - 敵が特殊溜め中は「クリスタル」へのヒットを優先
    //    - ヒット時: ダメージ/エフェクト再生/弾の無効化（プールへ返却）
    // =================================================================
    for (int bulletNum = 0; bulletNum < count; bulletNum++)
    {
        const auto bullet = bullet_creator.GetBullet(bulletNum);
        if (!bullet || !bullet->IsActive()) continue;

        // 弾は球として扱う（中心＋半径）
        const VECTOR sphereCenter = bullet->GetPosition();
        const float  sphereRadius = bullet->GetBulletRadius();

        const auto enemyState = ObjectAccessor::GetObjectAccessor().GetEnemyStateKind();

        // -----------------------------
        // 3-1) クリスタルへのヒットチェック
        //      敵が特殊溜め中のみ、弾がクリスタルを破壊できる
        // -----------------------------
        if (enemyState == EnemyStateKind::STATE_SPECIAL_CHARGE && crystal)
        {
            const bool hitCrystal = Collision::CheckSphereCapsuleCollision(
                sphereCenter, sphereRadius,
                crystal->GetPosition(), crystal->GetCapsuleRadius(), crystal->GetCapsuleHeight());

            if (hitCrystal)
            {
                crystal->TakeDamage(BULLET_DAMAGE_TO_CRYSTAL);

                // 破壊時と通常ヒット時でエフェクトを分ける
                if (crystal->IsDead())
                {
                    crystal->ChangeBreak();
                    EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BreakCrystal, sphereCenter);
                }
                else
                {
                    EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BulletHit, sphereCenter);
                }

                // 弾はプールへ返却
                bullet->ChangeActiveFalse();
                bullet->ResetPosition();
                continue;
            }
        }
        // -----------------------------
        // 3-2) 敵へのヒットチェック
        // -----------------------------
        else if (enemy)
        {
            // NOTE:
            // ここは「特殊溜め/特殊攻撃中は（敵本体への判定を抑制したい）」意図と思われるが、
            // OR 条件のため現状は常に true になりやすい。
            // 挙動変更を避けるためロジックはそのまま、意図だけコメントに留める。
            if (enemyState != EnemyStateKind::STATE_SPECIAL_CHARGE ||
                enemyState != EnemyStateKind::STATE_SPECIALATTACK)
            {
                const bool hitEnemy = Collision::CheckSphereCapsuleCollision(
                    sphereCenter, sphereRadius,
                    enemy->GetPosition(), enemy->GetCapsuleRadius(), enemy->GetCapsuleHeight());

                if (hitEnemy)
                {
                    enemy->TakeDamage(BULLET_DAMAGE_TO_ENEMY);
                    EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BulletHit, sphereCenter);

                    bullet->ChangeActiveFalse();
                    bullet->ResetPosition();
                    continue;
                }
            }
        }

        // -----------------------------
        // 3-3) プレイヤーへのヒットチェック
        //      （自弾/敵弾兼用のため、敵の弾が自分に当たるケースをここで処理）
        // -----------------------------
        if (player)
        {
            const bool hitPlayer = Collision::CheckSphereCapsuleCollision(
                sphereCenter, sphereRadius,
                ObjectAccessor::GetObjectAccessor().GetPlayerPosition(),
                player->GetCapsuleRadius(), player->GetCapsuleHeight());

            if (hitPlayer)
            {
                // 被弾時の演出：振動 + ダメージ + カメラシェイク + ヒットエフェクト
                StartJoypadVibration(DX_INPUT_PAD1, JOYPAD_VIBERATON_POWER, JOYPAD_VIBERATON_TIME, -1);

                if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIALATTACK)
                {
                    player->TakeDamage(SEPCIALBULLET_DAMAGE_TO_PLAYER);

                }
                else
                {
                    player->TakeDamage(BULLET_DAMAGE_TO_PLAYER);
                }
                ObjectAccessor::GetObjectAccessor().StartShakeCamera();
                EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BulletHit, player->GetPosition());

                bullet->ChangeActiveFalse();
                bullet->ResetPosition();
                continue;
            }
        }
    }
}