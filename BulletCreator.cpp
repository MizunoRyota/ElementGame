#include "stdafx.hpp"
#include "Bullet.hpp"
#include "BulletCreator.hpp"

BulletCreator::BulletCreator()
{}

BulletCreator::~BulletCreator()
{}

void BulletCreator::Initialize()
{
	for (int num = 0; num < BULLET_NUM; num++)
	{
		bullets.push_back(std::make_shared<Bullet>());
	}
}

void BulletCreator::CreateBullet()
{
	for (auto & bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->ChangeActiveTrue();
		}
	}
}

void BulletCreator::ShotStraight(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	for (auto & bullet : bullets )
	{
		bullet->Initialize(pos, dir, speed);
	}
}

void BulletCreator::Draw()
{
	for (auto & bullet : bullets)
	{
		bullet->Draw();
	}
}