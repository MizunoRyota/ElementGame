#include "stdafx.hpp"
#include "BulletFire.hpp"
#include "GameObject.hpp"
#include "BulletCreator.hpp"

BulletFire::BulletFire()
{
	bullet_firecooltimer = 0;
}

BulletFire::~BulletFire()
{
}

/// <summary>
/// 直線発射
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
void BulletFire::FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	//クールタイム中なら発射しない
	if (bullet_firecooltimer > 0) return;
	
	//クールタイムリセット
	bullet_firecooltimer = BULLET_COOLTIME;

	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed);

}

/// <summary>
/// 拡散発射
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
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

	float bullet_rotate = DX_TWO_PI_F / 6.0f;

	for (int num = 0; num < DIFFUSION_NUM; num++)
	{

		BulletCreator::GetBulletCreator().CreateBullet(pos, forward, speed);

		forward = BulletRotateVertical(forward, bullet_rotate);

	}

}

void BulletFire::FireHoming(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	BulletCreator::GetBulletCreator().CreateBullet(pos, dir, speed);
}

void BulletFire::FireSpecialAttack(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	////正面の向き
	//VECTOR forward = VGet(0, 0, 1);

	//forward = VNorm(forward); // 正規化

	//float bullet_rotate = DX_TWO_PI_F / 6.0f;

	//for (int num = 0; num < ALLRANGE_NUM; num++)
	//{

	//	BulletCreator::GetBulletCreator().CreateBullet(pos, forward, speed);

	//	forward = BulletRotateHorizontal(forward, bullet_rotate);

	//}
	constexpr int VERTICAL_NUM = 3; // 垂直方向の分割数
	constexpr int HORIZONTAL_NUM = ALLRANGE_NUM; // 水平方向の分割数

	// 基準方向（正規化）
	VECTOR forward = VNorm(dir);

	for (int v = 0; v < VERTICAL_NUM; ++v)
	{
		// elevation: 0(上)～π(下)
		float elevation = DX_PI_F * (v + 0.5f) / VERTICAL_NUM; // 0.5で中心寄り

		for (int h = 0; h < HORIZONTAL_NUM; ++h)
		{
			// azimuth: 0～2π
			float azimuth = DX_TWO_PI_F * h / HORIZONTAL_NUM;

			// 球面座標から方向ベクトルを計算
			VECTOR dirVec;
			dirVec.x = sinf(elevation) * cosf(azimuth);
			dirVec.y = cosf(elevation);
			dirVec.z = sinf(elevation) * sinf(azimuth);

			// 発射位置・方向・速度で弾生成
			BulletCreator::GetBulletCreator().CreateBullet(pos, dirVec, speed);
		}
	}
}

void BulletFire::FireUpdate()
{
	//クールタイム更新
	if (bullet_firecooltimer > 0)
	{
		bullet_firecooltimer--;
	}
}

/// <summary>
/// 弾の水平向き変更
/// </summary>
/// <param name="dir"></param>
/// <param name="angle"></param>
/// <returns></returns>
VECTOR BulletFire::BulletRotateHorizontal(const VECTOR& dir, float angle)
{

	float cos = cosf(angle);

	float sin = sinf(angle);

	return VGet(dir.x * cos - dir.z * sin,
				dir.y,
				dir.x * sin + dir.z * cos
	);
}

/// <summary>
/// 弾の垂直向き変更
/// </summary>
/// <param name="dir"></param>
/// <param name="angle"></param>
/// <returns></returns>
VECTOR BulletFire::BulletRotateVertical(const VECTOR& dir, float angle)
{

	float cos = cosf(angle);

	float sin = sinf(angle);

	// X軸回転行列を適用
	return VGet(
		dir.x,
		dir.y * cos - dir.z * sin,
		dir.y * sin + dir.z * cos
	);
}