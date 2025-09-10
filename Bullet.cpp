#include "stdafx.hpp"
#include "Pallet.hpp"
#include "Bullet.hpp"

Bullet::Bullet()
{
	bullet_isactive = false;
}
Bullet::~Bullet()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
void Bullet::Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	bullet_position = pos;
	bullet_direction = dir;
	bullet_speed = speed;
	bullet_life = BULLET_LIFE;

	ChangeActiveTrue();
}

/// <summary>
/// 更新
/// </summary>
void Bullet::Update()
{
	if (!IsActive()) return;

	Move();

	if (bullet_life <= 0)
	{
		ChangeActiveFalse();
		ResetPosition();
	}
}

/// <summary>
/// 移動
/// </summary>
void Bullet::Move()
{
	bullet_life -= BULLET_COUNT;
	bullet_direction = VNorm(bullet_direction);
	bullet_direction = VScale(bullet_direction, bullet_speed);
	bullet_position = VAdd(bullet_position, bullet_direction);
}

/// <summary>
/// アクティブ状態をFALSEに変更
/// </summary>
void Bullet::ChangeActiveFalse()
{
	bullet_isactive = false;
}
/// <summary>
/// アクティブ状態をTUREに変更
/// </summary>
void Bullet::ChangeActiveTrue()
{
	bullet_isactive = true;
}
/// <summary>
/// 弾のポジションを初期化
/// </summary>
void Bullet::ResetPosition()
{
	bullet_position = VGet(0, 0, 0);
}

/// <summary>
/// 描画
/// </summary>
void Bullet::Draw()
{
	DrawSphere3D(bullet_position, 0.3f, 20, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);
}