#include "Dxlib.h"
#include "Pallet.hpp"
#include "Bullet.hpp"
#include "BulletManager.hpp"

BulletManager::BulletManager()
{
	for (int num = 0; num < BulletNum; num++)
	{
		bullet[num] = NULL;
	}
}

BulletManager::~BulletManager()
{
}

void BulletManager::Update()
{
	if (cooldown_timer > 0) {
		cooldown_timer--; // クールダウン経過
	}
	for (int num = 0; num < BulletNum; num++)
	{
		//NULLでない場合
		if (bullet[num] != NULL)
		{
			bullet[num]->Update();
			if (bullet[num]->CheckBulletOut() == true)
			{
				
			}
		}
	}
}

void BulletManager::Shot(const VECTOR& position, const VECTOR& direction)
{	
	// クールダウン中は発射できない
	if (cooldown_timer > 0) {
		return;
	}

	for (int num = 0; num < BulletNum; num++)
	{
		if (bullet[num] == NULL)
		{
			bullet[num] = std::make_shared<Bullet>(position, direction);
			cooldown_timer = CooldownTime; // 撃ったらクールダウン開始
			break;
		}
	}
}

const VECTOR BulletManager::GetBulletPosition()
{
	for (int num = 0; num < BulletNum; num++) {
		//NULLでない場合
		if (bullet[num] != NULL) {
			return bullet[num].get()->GetPosition();
		}
	}
}

void BulletManager::Draw()
{
	for (int num = 0; num < BulletNum; num++)
	{
		//NULLでない場合
		if (bullet[num] != NULL)
		{
			bullet[num]->Draw();
		}
	}
}