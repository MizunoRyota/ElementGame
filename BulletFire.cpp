#include "stdafx.hpp"
#include "BulletFire.hpp"
#include "GameObject.hpp"
#include "BulletCreator.hpp"
#include "Player.hpp"
#include "EffectCreator.hpp"
#include "src/Sounds/SoundManager.hpp"

BulletFire::BulletFire()
{
	bullet_fire_cooltimer = 0; // 発射クール初期化
}

BulletFire::~BulletFire() {}

// エフェクト種別への変換
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
	case EffectFlavor::FireGround:return (int)ET::FireGround;
	case EffectFlavor::BulletPlayer:return (int)ET::BulletPlayer;
	}
	return (int)ET::BulletWind; // 既定
}

// 直進弾
void BulletFire::FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_fire_cooltimer > 0) return; // クール中
	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed, ToEffectIndex(EffectFlavor::BulletFire));
}

// プレイヤー弾
void BulletFire::FirePlayer(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_fire_cooltimer > 0) return; // クール中
	
	SoundManager::GetSoundManager().PlayFireSe();

	bullet_fire_cooltimer = BULLET_COOLTIME; // クール開始
	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed, ToEffectIndex(EffectFlavor::BulletPlayer));
}

// 拡散弾
void BulletFire::FireDiffusion(const VECTOR& pos, const VECTOR& dir, const float& speed)
{

	SoundManager::GetSoundManager().PlayFireSe();


	VECTOR bulletForword = VNorm(dir); // 基準方向
	float bulletRotate = DX_TWO_PI_F / DIFFUSION_RADIUS; // 回転角
	bulletForword = BulletRotateHorizontal(bulletForword, -bulletRotate * DIFFUSION_OFFSET); // 初期ずらし
	for (int bullet_num = 0; bullet_num < DIFFUSION_NUM; bullet_num++)
	{
		BulletCreator::GetBulletCreator().CreateBullet(pos, bulletForword, speed, ToEffectIndex(EffectFlavor::BulletWater));
		bulletForword = BulletRotateHorizontal(bulletForword, bulletRotate);
	}
}

// 垂直散弾
void BulletFire::FireVertical(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	VECTOR bulletForword = VNorm(dir);
	float bulletRotate = DX_TWO_PI_F / DIFFUSION_RADIUS;
	for (int bullet_num = 0; bullet_num < DIFFUSION_NUM; bullet_num++)
	{
		BulletCreator::GetBulletCreator().CreateBullet(pos, bulletForword, speed, ToEffectIndex(EffectFlavor::BulletFire));
		bulletForword = BulletRotateVertical(bulletForword, bulletRotate);
	}
}

// ホーミング弾
void BulletFire::FireHoming(const VECTOR& pos,
	const VECTOR& dir,
	const float& speed,
	const std::shared_ptr<GameObject>& target)
{
	if (bullet_fire_cooltimer > 0) return;

	SoundManager::GetSoundManager().PlayFireSe();

	bullet_fire_cooltimer = BULLET_COOLTIME;
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
		ToEffectIndex(EffectFlavor::BulletWind));
}

// 全方位落下など特殊攻撃
void BulletFire::FireSpecialAttack(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	if (bullet_fire_cooltimer > 0) return;

	SoundManager::GetSoundManager().PlayExplosionSe();


	bullet_fire_cooltimer = BULLET_COOLTIME;

	int specialRingNum = 16;                 // 外周弾数
	const VECTOR downDir = VGet(0.0f, -1.0f, 0.0f);

	for (int ring = 0; ring < INNER_RINGS; ++ring)
	{
		float radius = RING_RADIUS - ring * RADIUS_STEP;
		specialRingNum--; // 内側ほど密に
		if (radius <= 0.0f) continue;
		for (int bullet_i = 0; bullet_i < specialRingNum; bullet_i++)
		{
			float t = (float)bullet_i / specialRingNum;
			float ang = DX_TWO_PI_F * t;
			VECTOR offset = VGet(cosf(ang) * radius, DROP_HEIGHT, sinf(ang) * radius);
			VECTOR spawnPos = VAdd(pos, offset);
			BulletCreator::GetBulletCreator().CreateBullet(spawnPos, downDir, speed, ToEffectIndex(EffectFlavor::BulletSpecial));

			// マーカー表示等を行うならここで groundPos を使用
			VECTOR groundPos = VAdd(pos, VGet(cosf(ang) * radius, 0.0f, sinf(ang) * radius));
		}
	}
}

// クールタイマ更新
void BulletFire::FireUpdate()
{
	if (bullet_fire_cooltimer > 0) bullet_fire_cooltimer--;
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