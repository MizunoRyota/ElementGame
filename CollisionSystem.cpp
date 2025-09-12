#include "stdafx.hpp"
#include "CollisionSystem.hpp"
#include "SharedData.hpp"
#include "BulletCreator.hpp"
#include "Bullet.hpp"
#include "Collision.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

namespace
{
	constexpr int BULLET_DAMAGE_TO_ENEMY   = 10;
	constexpr int BULLET_DAMAGE_TO_PLAYER = 10;
}

// 当たり判定用の暫定パラメータ(モデルに合わせて調整)
namespace
{
	// 敵のカプセル設定
	constexpr float ENEMY_CAPSULE_RADIUS = 0.6f;
	constexpr float ENEMY_CAPSULE_HEIGHT = 1.0f;

	// プレイヤーのカプセル設定
	constexpr float PLAYER_CAPSULE_RADIUS = 0.5f;
	constexpr float PLAYER_CAPSULE_HEIGHT = 1.0f;

	// カプセル基点は足元とし、Y+ に高さ
	inline VECTOR MakeCapsuleTop(const VECTOR& base, float height)
	{
		return VAdd(base, VGet(0.0f, height, 0.0f));
	}
}

void CollisionSystem::Resolve(SharedData& shared)
{
	// 必要な参照を取得
	auto enemy  = std::dynamic_pointer_cast<Enemy>(shared.FindObject("Enemy"));
	auto player = std::dynamic_pointer_cast<Player>(shared.FindObject("Player"));

	auto& bc = BulletCreator::GetBulletCreator();

	// 敵のカプセル(下端) = ワールド座標の足元位置と仮定
	VECTOR enemyBase{};
	if (enemy)
	{
		enemyBase = enemy->GetPosition();
		(void)MakeCapsuleTop(enemyBase, ENEMY_CAPSULE_HEIGHT); // 使わないが高さはここで管理
	}

	// プレイヤーのカプセル(下端)
	VECTOR playerBase{};
	if (player)
	{
		playerBase = player->GetPosition();
		(void)MakeCapsuleTop(playerBase, PLAYER_CAPSULE_HEIGHT);
	}

	const int count = bc.GetBulletCount();
	for (int i = 0; i < count; ++i)
	{
		const auto bullet = bc.GetBullet(i);
		if (!bullet || !bullet->IsActive()) continue;

		const VECTOR sphereCenter = bullet->GetPosition();
		const float  sphereRadius = Bullet::BULLET_RADIUS;

		// 敵へのヒットチェック
		if (enemy)
		{
			const bool hitEnemy = Collision::CheckSphereCapsuleCollision(
				sphereCenter, sphereRadius, enemyBase, enemy->GetCapsuleRadius(), enemy->GetCapsuleHeight());

			if (hitEnemy)
			{
				if (enemy->TakeDamage(BULLET_DAMAGE_TO_ENEMY))
				{
					// TODO: ヒットエフェクト等
				}
				bullet->ChangeActiveFalse();
				bullet->ResetPosition();

				continue; // 既に消えているため次の弾へ
			}
		}

		// プレイヤーへのヒットチェック
		if (player)
		{
			const bool hitPlayer = Collision::CheckSphereCapsuleCollision(
				sphereCenter, sphereRadius, playerBase, player->GetCapsuleRadius(), player->GetCapsuleHeight());

			if (hitPlayer)
			{
				if (player->TakeDamage(BULLET_DAMAGE_TO_PLAYER))
				{
					// TODO: 画面揺れ, 無敵演出, 効果音等
				}
				bullet->ChangeActiveFalse();
				bullet->ResetPosition();
			}
		}
	}
}