#include "stdafx.hpp"
#include "CollisionSystem.hpp"
#include "SharedData.hpp"
#include "BulletCreator.hpp"
#include "Bullet.hpp"
#include "Collision.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Crystal.hpp"
#include "Camera.hpp"
#include "EffectCreator.hpp" // 追加

namespace
{
	constexpr int BULLET_DAMAGE_TO_ENEMY   = 1;
	constexpr int BULLET_DAMAGE_TO_CRYSTAL = 1;
	constexpr int BULLET_DAMAGE_TO_PLAYER = 10;
}

//// 当たり判定用の暫定パラメータ(モデルに合わせて調整)
//namespace
//{
//	// カプセル基点は足元とし、Y+ に高さ
//	inline VECTOR MakeCapsuleTop(const VECTOR& base, float height)
//	{
//		return VAdd(base, VGet(0.0f, height, 0.0f));
//	}
//}

void CollisionSystem::Resolve(SharedData& shared)
{
	// 必要な参照を取得
	auto enemy = std::dynamic_pointer_cast<Enemy>(shared.FindObject("Enemy"));
	auto player = std::dynamic_pointer_cast<Player>(shared.FindObject("Player"));
	auto crystal = std::dynamic_pointer_cast<Crystal>(shared.FindObject("Crystal"));
	auto camera = std::dynamic_pointer_cast<Camera>(shared.FindObject("Camera"));

	auto& bullet_creator = BulletCreator::GetBulletCreator();

	const int count = bullet_creator.GetBulletCount();

	for (int bulletNum = 0; bulletNum < count; bulletNum++)
	{
		const auto bullet = bullet_creator.GetBullet(bulletNum);
		if (!bullet || !bullet->IsActive()) continue;

		const VECTOR sphereCenter = bullet->GetPosition();
		const float  sphereRadius = bullet->GetBulletRadius();
		//クリスタルへのヒットチェック
		if (enemy->GetEnemyState() == STATE_SPECIAL_CHARGE)
		{
			const bool hitCrystal = Collision::CheckSphereCapsuleCollision(
				sphereCenter, sphereRadius, crystal->GetPosition(), crystal->GetCapsuleRadius(), crystal->GetCapsuleHeight());

			if (hitCrystal)
			{
				crystal->TakeDamage(BULLET_DAMAGE_TO_CRYSTAL);

				if (crystal->IsDead())
				{
					crystal->ChangeBreak();
					enemy->ChangeStatePalsy();
					player->PrepareLaser();
					EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BreakCrystal, sphereCenter);
				}
				else
				{
					// 弾ヒットエフェクト
					EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BulletHit, sphereCenter);
				}

				bullet->ChangeActiveFalse();
				bullet->ResetPosition();

				continue; // 既に消えているため次の弾へ
			}
		}
		// 敵へのヒットチェック
		else if (enemy->GetEnemyState() != STATE_SPECIAL_CHARGE)
		{
			bool hitEnemy = false;
			if (true)
			{
				hitEnemy = Collision::CheckSphereCapsuleCollision(
					sphereCenter, sphereRadius, enemy->GetPosition(), enemy->GetCapsuleRadius(), enemy->GetCapsuleHeight());
			}
			//hitEnemy = Collision::CheckSegmentSegmentColliison();
			if (hitEnemy)
			{
				enemy->TakeDamage(BULLET_DAMAGE_TO_ENEMY);

				// 弾ヒットエフェクト
				EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BulletHit, sphereCenter);
				bullet->ChangeActiveFalse();
				bullet->ResetPosition();

				continue; // 既に消えているため次の弾へ
			}

		}

		// プレイヤーへのヒットチェック
		if (player)
		{
			const bool hitPlayer = Collision::CheckSphereCapsuleCollision(
				sphereCenter, sphereRadius, player->GetPosition(), player->GetCapsuleRadius(), player->GetCapsuleHeight());

			if (hitPlayer)
			{
				player->TakeDamage(BULLET_DAMAGE_TO_PLAYER);
				camera->StartShakeCamera();
				// エフェクト: 被弾
				EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BulletHit, player->GetPosition());

				bullet->ChangeActiveFalse();
				bullet->ResetPosition();
			}
		}
	}
}