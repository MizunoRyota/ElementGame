#include "Dxlib.h"
#include "Pallet.hpp"
#include "Bullet.hpp"

Bullet::Bullet(const VECTOR& position, const VECTOR& direction)
	:position(VGet(0,0,0))
	,direction(VGet(0,0,0))
{
	this->position = position;
	this->direction = direction;
	prev_positon = position;
}

Bullet::~Bullet() {

}

void Bullet::Initialize()
{

}

void Bullet::Update()
{
	direction = VNorm(direction);
	direction = VScale(direction, BulletSpeed);
	position = VAdd(position, direction);
}

bool Bullet::CheckBulletOut()
{
	float bullet_range = VSize(VSub(position, prev_positon));
	return (bullet_range > BulletRange || bullet_range < -BulletRange);
}

void Bullet::Draw()
{
	DrawSphere3D(position, 0.3f, 20, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);
}