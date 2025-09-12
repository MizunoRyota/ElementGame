#include "stdafx.hpp"
#include "BulletFire.hpp"
#include "GameObject.hpp"
#include "BulletCreator.hpp"
#include "Player.hpp"   // 追加

BulletFire::BulletFire()
{
	bullet_firecooltimer = 0;
}

BulletFire::~BulletFire() {}

void BulletFire::FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	//クールタイム中なら発射しない
	if (bullet_firecooltimer > 0) return;
	
	//クールタイムリセット
	bullet_firecooltimer = BULLET_COOLTIME;

	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed);

}

void BulletFire::FireDiffusion(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	//正面の向き
	VECTOR forward = dir;

	forward = VNorm(forward); // 正規化

	float bullet_rotate = DX_TWO_PI_F / 30.0f;

	forward = BulletRotateHorizontal(forward, -bullet_rotate);

	for (int num = 0; num < DIFFUSION_NUM; num++)
	{
		BulletCreator::GetBulletCreator().CreateBullet(pos, forward, speed);

		forward = BulletRotateHorizontal(forward, bullet_rotate);

	}

}

void BulletFire::FireVirtical(const VECTOR& pos, const VECTOR& dir, const float& speed)
{

	//正面の向き
	VECTOR forward = dir;

	forward = VNorm(forward); // 正規化

	float bullet_rotate = DX_TWO_PI_F / 30.0f;

	for (int num = 0; num < DIFFUSION_NUM; num++)
	{

		BulletCreator::GetBulletCreator().CreateBullet(pos, forward, speed);


		forward = BulletRotateVertical(forward, bullet_rotate);

	}

}

// 追加: 追尾時間限定ホーミング
void BulletFire::FireHoming(const VECTOR& pos,
	const VECTOR& dir,
	const float& speed,
	const std::shared_ptr<GameObject>& target)
{
	//クールタイム中なら発射しない
	if (bullet_firecooltimer > 0) return;

	//クールタイムリセット
	bullet_firecooltimer = BULLET_COOLTIME;

	BulletCreator::GetBulletCreator().CreateHomingBullet(
		pos,
		dir,
		speed,
		[targetWeak = std::weak_ptr<GameObject>(target)]()
		{
			if (auto sp = targetWeak.lock())
			{
				return sp->GetTarget();
			}
			return VGet(0, 0, 0);
		},
		HOMING_DURATION,
		HOMING_TURN_SPEED
	);
}

void BulletFire::FireSpecialAttack(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	constexpr int VERTICAL_NUM = 30;
	constexpr int HORIZONTAL_NUM = ALLRANGE_NUM;
	VECTOR forward = VNorm(dir);
	for (int v = 0; v < VERTICAL_NUM; ++v)
	{
		float elevation = DX_TWO_PI_F * (v + 0.5f) / VERTICAL_NUM;
		for (int h = 0; h < HORIZONTAL_NUM; ++h)
		{
			float azimuth = DX_TWO_PI_F * h / HORIZONTAL_NUM;
			VECTOR dirVec;
			dirVec.x = sinf(elevation) * cosf(azimuth);
			dirVec.y = cosf(elevation);
			dirVec.z = sinf(elevation) * sinf(azimuth);
			BulletCreator::GetBulletCreator().CreateBullet(pos, dirVec, speed);
		}
	}
}

void BulletFire::FireUpdate()
{
	//クールタイム更新
	if (bullet_firecooltimer > 0) bullet_firecooltimer--;
}

VECTOR BulletFire::BulletRotateHorizontal(const VECTOR& dir, float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	return VGet(dir.x * c - dir.z * s, dir.y, dir.x * s + dir.z * c);
}

VECTOR BulletFire::BulletRotateVertical(const VECTOR& dir, float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	return VGet(dir.x, dir.y * c - dir.z * s, dir.y * s + dir.z * c);
}