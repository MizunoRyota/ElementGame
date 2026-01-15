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

void BulletCreator::Initialize() 
{
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->ChangeActiveFalse();
			break;
		}
	}
}

void BulletCreator::CreateBullet(const VECTOR& pos, const VECTOR& dir, const float& speed, int effectTypeIndex)
{
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Initialize(pos, dir, speed, effectTypeIndex);
			break;
		}
	}
}

void BulletCreator::CreateHomingBullet(const VECTOR& pos, const VECTOR& dir, const float& speed, std::function<VECTOR()> targetGetter, float homingDuration, float turnSpeedRad, int effectTypeIndex)
{
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->InitializeHoming(pos, dir, speed, std::move(targetGetter), homingDuration, turnSpeedRad, effectTypeIndex);
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

void BulletCreator::StopBulletEffect()
{
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->StopEffect();
		}
	}
}