#include "stdafx.hpp"
#include "Bullet.hpp"
#include "BulletCreator.hpp"

BulletCreator::BulletCreator()
{
	for (int num = 0; num < BULLET_NUM; num++)
	{
		bullets.push_back(std::make_shared<Bullet>());
	}
}

BulletCreator::~BulletCreator() {}

void BulletCreator::Initialize() {}

void BulletCreator::CreateBullet(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Initialize(pos, dir, speed);
			break;
		}
	}
}

// 追加: ホーミング弾
void BulletCreator::CreateHomingBullet(const VECTOR& pos,
	const VECTOR& dir,
	float speed,
	std::function<VECTOR()> targetGetter,
	float homingTime,
	float turnSpeedRad)
{
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->InitializeHoming(pos, dir, speed, std::move(targetGetter), homingTime, turnSpeedRad);
			break;
		}
	}
}

void BulletCreator::Update()
{
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Update();
		}
	}
}

void BulletCreator::Draw()
{
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Draw();
		}
	}
}