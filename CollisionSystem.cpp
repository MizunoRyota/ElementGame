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
#include "EffectCreator.hpp" // 追加
#include "ObjectAccessor.hpp"

namespace
{
	constexpr int BULLET_DAMAGE_TO_ENEMY   = 1;
	constexpr int BULLET_DAMAGE_TO_CRYSTAL = 1;
	constexpr int BULLET_DAMAGE_TO_PLAYER = 10;
	constexpr float KNOCKBACK_DISTANCE = 0.1f;
	constexpr float PLAYER_KNOCKBACK_RADIUS = 2.0f;
	constexpr float ENEMY_KNOCKBACK_RADIUS = 2.0f;
	constexpr float ENEMY_SPECIAL_KNOCKBACK_RADIUS = 5.0f;

}

void CollisionSystem::Resolve(SharedData& shared)
{
	auto enemy = std::dynamic_pointer_cast<Enemy>(shared.FindObject("Enemy"));
	auto player = std::dynamic_pointer_cast<Player>(shared.FindObject("Player"));
	auto crystal = std::dynamic_pointer_cast<Crystal>(shared.FindObject("Crystal"));

	auto& bullet_creator = BulletCreator::GetBulletCreator();

	const int count = bullet_creator.GetBulletCount();

	//キャラクター同士の当たり判定
	if (enemy && player)
	{
		bool hitPlayer = false;
		if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIAL_CHARGE || ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIALATTACK)
		{
			hitPlayer = Collision::CheckCapsuleCapsuleCollision(
				player->GetPosition(), PLAYER_KNOCKBACK_RADIUS, player->GetCapsuleHeight(),
				enemy->GetPosition(), ENEMY_SPECIAL_KNOCKBACK_RADIUS, enemy->GetCapsuleHeight());
		}
		else
		{
			hitPlayer = Collision::CheckCapsuleCapsuleCollision(
				player->GetPosition(), PLAYER_KNOCKBACK_RADIUS, player->GetCapsuleHeight(),
				enemy->GetPosition(), ENEMY_KNOCKBACK_RADIUS, enemy->GetCapsuleHeight());
		}

		if (hitPlayer)
		{
			VECTOR pushDir = VSub(player->GetPosition(), enemy->GetPosition());
			float knockbackDistance = VSquareSize(pushDir);
			//if (VSquareSize(pushDir) < 0.0001f)
			//{
			//	pushDir = VGet(0.0f, 0.0f, 1.0f);
			//}

			pushDir = VNorm(pushDir);

			if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIAL_CHARGE || ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIALATTACK)
			{
				player->ApplyKnockback(VScale(pushDir, Collision::GetCapsuleCapsuleMinDistance(
					player->GetPosition(), PLAYER_KNOCKBACK_RADIUS, player->GetCapsuleHeight(),
					enemy->GetPosition(), ENEMY_SPECIAL_KNOCKBACK_RADIUS, enemy->GetCapsuleHeight())));
			}
			else
			{
				player->ApplyKnockback(VScale(pushDir, Collision::GetCapsuleCapsuleMinDistance(
					player->GetPosition(), PLAYER_KNOCKBACK_RADIUS, player->GetCapsuleHeight(),
					enemy->GetPosition(), ENEMY_KNOCKBACK_RADIUS, enemy->GetCapsuleHeight())));
			}
		}
	}

	//レーザーと敵との当たり判定
	if (ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() == PlayerStateKind::STATE_LASER)
	{
		bool hitEnemy = false;

		hitEnemy = Collision::CheckSegmentSegmentColliison(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), ObjectAccessor::GetObjectAccessor().GetEnemyGetHitPosition(), ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition(), ObjectAccessor::GetObjectAccessor().GetLaserEndPosition());

		if (hitEnemy)
		{
			enemy->TakeDamage(BULLET_DAMAGE_TO_ENEMY);
		}
		return;
	}

	//弾とそれぞれのキャラクターの当たり判定
	for (int bulletNum = 0; bulletNum < count; bulletNum++)
	{
		const auto bullet = bullet_creator.GetBullet(bulletNum);
		if (!bullet || !bullet->IsActive()) continue;

		const VECTOR sphereCenter = bullet->GetPosition();
		const float  sphereRadius = bullet->GetBulletRadius();
		//クリスタルへのヒットチェック
		if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIAL_CHARGE)
		{
			const bool hitCrystal = Collision::CheckSphereCapsuleCollision(
				sphereCenter, sphereRadius, crystal->GetPosition(), crystal->GetCapsuleRadius(), crystal->GetCapsuleHeight());

			if (hitCrystal)
			{
				crystal->TakeDamage(BULLET_DAMAGE_TO_CRYSTAL);

				if (crystal->IsDead())
				{
					crystal->ChangeBreak();
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
		else if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() != EnemyStateKind::STATE_SPECIAL_CHARGE)
		{
			bool hitEnemy = false;

			hitEnemy = Collision::CheckSphereCapsuleCollision(
				sphereCenter, sphereRadius, enemy->GetPosition(), enemy->GetCapsuleRadius(), enemy->GetCapsuleHeight());

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
				sphereCenter, sphereRadius, ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), player->GetCapsuleRadius(), player->GetCapsuleHeight());

			if (hitPlayer)
			{
				player->TakeDamage(BULLET_DAMAGE_TO_PLAYER);
				ObjectAccessor::GetObjectAccessor().StartShakeCamera();
				// エフェクト: 被弾
				EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::BulletHit, player->GetPosition());

				bullet->ChangeActiveFalse();
				bullet->ResetPosition();
				continue;
			}
		}
	}
}