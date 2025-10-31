#include "stdafx.hpp"
#include "BulletFire.hpp"
#include "GameObject.hpp"
#include "BulletCreator.hpp"
#include "Player.hpp"
#include "EffectCreator.hpp"

BulletFire::BulletFire()
{
	bullet_firecooltimer = 0; // 発射クール初期化
}

BulletFire::~BulletFire() {}

// エフェクト種別への変換
int BulletFire::ToEffectIndex(EffectFlavor effect_flavor)
{
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
	return (int)ET::BulletHoming; // 既定
}

// 直進弾
void BulletFire::FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_firecooltimer > 0) return; // クール中
	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed, ToEffectIndex(EffectFlavor::Fire));
}

// プレイヤー弾
void BulletFire::FirePlayer(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_firecooltimer > 0) return; // クール中
	bullet_firecooltimer = BULLET_COOLTIME; // クール開始
	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed, ToEffectIndex(EffectFlavor::PlayerAttack));
}

// 拡散弾
void BulletFire::FireDiffusion(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	VECTOR bulletForword = VNorm(dir); // 基準方向
	float bulletRotate = DX_TWO_PI_F / DIFFUSION_RADIUS; // 回転角
	bulletForword = BulletRotateHorizontal(bulletForword, -bulletRotate * DIFFUSION_OFFSET); // 初期ずらし
	for (int num = 0; num < DIFFUSION_NUM; num++)
	{
		BulletCreator::GetBulletCreator().CreateBullet(pos, bulletForword, speed, ToEffectIndex(EffectFlavor::Water));
		bulletForword = BulletRotateHorizontal(bulletForword, bulletRotate);
	}
}

// 垂直散弾
void BulletFire::FireVirtical(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	VECTOR bulletForword = VNorm(dir);
	float bulletRotate = DX_TWO_PI_F / DIFFUSION_RADIUS;
	for (int num = 0; num < DIFFUSION_NUM; num++)
	{
		BulletCreator::GetBulletCreator().CreateBullet(pos, bulletForword, speed, ToEffectIndex(EffectFlavor::Fire));
		bulletForword = BulletRotateVertical(bulletForword, bulletRotate);
	}
}

// ホーミング弾
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

// 全方位落下など特殊攻撃
void BulletFire::FireSpecialAttack(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_firecooltimer > 0) return;
	bullet_firecooltimer = BULLET_COOLTIME;

	int specialRingNum = 16;                 // 外周弾数
	const VECTOR downDir = VGet(0.0f, -1.0f, 0.0f);

	for (int ring = 0; ring < INNER_RINGS; ++ring)
	{
		float radius = RING_RADIUS - ring * RADIUS_STEP;
		specialRingNum -= 1; // 内側ほど密に
		if (radius <= 0.0f) continue;
		for (int i = 0; i < specialRingNum; ++i)
		{
			float t = (float)i / specialRingNum;
			float ang = DX_TWO_PI_F * t;
			VECTOR offset = VGet(cosf(ang) * radius, DROP_HEIGHT, sinf(ang) * radius);
			VECTOR spawnPos = VAdd(pos, offset);
			BulletCreator::GetBulletCreator().CreateBullet(spawnPos, downDir, speed, ToEffectIndex(EffectFlavor::Special));

			// マーカー表示等を行うならここで groundPos を使用
			VECTOR groundPos = VAdd(pos, VGet(cosf(ang) * radius, 0.0f, sinf(ang) * radius));
		}
	}
}

// クールタイマ更新
void BulletFire::FireUpdate()
{
	if (bullet_firecooltimer > 0) bullet_firecooltimer--;
}

// 水平方向の回転
VECTOR BulletFire::BulletRotateHorizontal(const VECTOR& dir, float angle)
{
	float c = cosf(angle); float s = sinf(angle);
	return VGet(dir.x * c - dir.z * s, dir.y, dir.x * s + dir.z * c);
}

// 垂直方向の回転
VECTOR BulletFire::BulletRotateVertical(const VECTOR& dir, float angle)
{
	float c = cosf(angle); float s = sinf(angle);
	return VGet(dir.x, dir.y * c - dir.z * s, dir.y * s + dir.z * c);
}