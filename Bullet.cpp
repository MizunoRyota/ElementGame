#include "stdafx.hpp"
#include "Pallet.hpp"
#include "Bullet.hpp"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	bullet_position = pos;
	bullet_direction = dir;
	bullet_speed = speed;
	ChangeActiveTrue();
}

void Bullet::Update()
{
	if (!IsActive()) return;

	bullet_direction = VNorm(bullet_direction);
	bullet_direction = VScale(bullet_direction, bullet_speed);
	bullet_position = VAdd(bullet_position, bullet_direction);

}

void Bullet::ChangeActiveFalse()
{
	bullet_isactive = false;
}

void Bullet::ChangeActiveTrue()
{
	bullet_isactive = true;
}

void Bullet::Draw()
{
	DrawSphere3D(bullet_position, 0.3f, 20, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);
}