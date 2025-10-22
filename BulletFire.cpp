#include "stdafx.hpp"
#include "BulletFire.hpp"
#include "GameObject.hpp"
#include "BulletCreator.hpp"
#include "Player.hpp"   // 追加
#include "EffectCreator.hpp" // 追加

BulletFire::BulletFire()
{
	bullet_firecooltimer = 0; // 発射クール残フレーム
}

BulletFire::~BulletFire() {}

int BulletFire::ToEffectIndex(EffectFlavor effect_flavor)
{
	// EffectFlavor -> EffectCreator::EffectType 対応
	using ET = EffectCreator::EffectType;
	switch (effect_flavor)
	{
	case EffectFlavor::Fire:return (int)ET::BulletStraight;
	case EffectFlavor::Water:return (int)ET::BulletDiffusion;
	case EffectFlavor::Wind:return (int)ET::BulletHoming;
	case EffectFlavor::Special:return (int)ET::BulletSpecial;
	case EffectFlavor::Hit:return (int)ET::BulletHit;
	case EffectFlavor::FireGround:return (int)ET::FireGround;
	case EffectFlavor::PlayerAttack:return (int)ET::BulletPlayer;

	}
	return (int)ET::BulletHoming; // デフォルト:風
}

void BulletFire::FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_firecooltimer > 0) return; // クール中
	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed, ToEffectIndex(EffectFlavor::Fire));
}

void BulletFire::FirePlayer(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_firecooltimer > 0) return; // クール中
	bullet_firecooltimer = BULLET_COOLTIME; // リセット
	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed, ToEffectIndex(EffectFlavor::PlayerAttack));
}

void BulletFire::FireDiffusion(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	VECTOR forward = VNorm(dir); // 基準方向
	float bullet_rotate = DX_TWO_PI_F / DIFFUSION_RADIUS; // 分割角
	forward = BulletRotateHorizontal(forward, -bullet_rotate * DIFFUSION_OFFSET); // 初期オフセット
	for (int num = 0; num < DIFFUSION_NUM; num++)
	{
		BulletCreator::GetBulletCreator().CreateBullet(pos, forward, speed, ToEffectIndex(EffectFlavor::Water));
		forward = BulletRotateHorizontal(forward, bullet_rotate);
	}
}

void BulletFire::FireVirtical(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	VECTOR forward = VNorm(dir);
	float bullet_rotate = DX_TWO_PI_F / DIFFUSION_RADIUS;
	for (int num = 0; num < DIFFUSION_NUM; num++)
	{
		BulletCreator::GetBulletCreator().CreateBullet(pos, forward, speed, ToEffectIndex(EffectFlavor::Fire));
		forward = BulletRotateVertical(forward, bullet_rotate);
	}
}

void BulletFire::FireHoming(const VECTOR& pos,
	const VECTOR& dir,
	const float& speed,
	const std::shared_ptr<GameObject>& target)
{
	if (bullet_firecooltimer > 0) return;
	bullet_firecooltimer = BULLET_COOLTIME;
	BulletCreator::GetBulletCreator().CreateHomingBullet(
		pos,
		dir,
		speed,
		[targetWeak = std::weak_ptr<GameObject>(target)]()
		{
			if (auto sp = targetWeak.lock()) return sp->GetTarget();
			return VGet(0, 0, 0);
		},
		HOMING_DURATION,
		HOMING_TURN_SPEED,
		ToEffectIndex(EffectFlavor::Wind));
}

void BulletFire::FireSpecialAttack(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_firecooltimer > 0) return;
	bullet_firecooltimer = BULLET_COOLTIME;

	int RING_BULLET_NUM = 16;                 // 外周初期弾数

	const VECTOR downDir = VGet(0.0f, -1.0f, 0.0f); // 落下方向

	for (int ring = 0; ring < INNER_RINGS; ++ring)
	{
		float radius = RING_RADIUS - ring * RADIUS_STEP;
		RING_BULLET_NUM -= 1; // 内側ほど減らす
		if (radius <= 0.0f) continue;
		for (int i = 0; i < RING_BULLET_NUM; ++i)
		{
			float t = (float)i / RING_BULLET_NUM;
			float ang = DX_TWO_PI_F * t;
			VECTOR offset = VGet(cosf(ang) * radius, DROP_HEIGHT, sinf(ang) * radius);
			VECTOR spawnPos = VAdd(pos, offset);
			BulletCreator::GetBulletCreator().CreateBullet(spawnPos, downDir, speed, ToEffectIndex(EffectFlavor::Special));

			// (将来) マーカー表示: 現状は DrawMarkers() に任せる
			VECTOR groundPos = VAdd(pos, VGet(cosf(ang) * radius, 0.0f, sinf(ang) * radius));

		}
	}
}

void BulletFire::FireUpdate()
{
	if (bullet_firecooltimer > 0) bullet_firecooltimer--; // クール減算
}

VECTOR BulletFire::BulletRotateHorizontal(const VECTOR& dir, float angle)
{
	float c = cosf(angle); float s = sinf(angle);
	return VGet(dir.x * c - dir.z * s, dir.y, dir.x * s + dir.z * c);
}

VECTOR BulletFire::BulletRotateVertical(const VECTOR& dir, float angle)
{
	float c = cosf(angle); float s = sinf(angle);
	return VGet(dir.x, dir.y * c - dir.z * s, dir.y * s + dir.z * c);
}