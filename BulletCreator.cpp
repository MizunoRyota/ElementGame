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

BulletCreator::~BulletCreator()
{}
/// <summary>
/// ’e‚Ì‰Šú‰»
/// </summary>
void BulletCreator::Initialize()
{

}

/// <summary>
/// ’e‚ğì¬
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
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

/// <summary>
/// XV
/// </summary>
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

/// <summary>
/// •`‰æ
/// </summary>
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