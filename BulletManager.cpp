#include "Dxlib.h"
#include "Pallet.hpp"
#include "Bullet.hpp"
#include "BulletManager.hpp"

BulletManager::BulletManager()
	:cooldown_timer (0)
{
	for (int num = 0; num < BulletNum; num++)
	{
		bullet[num] = NULL;
	}
}

BulletManager::~BulletManager()
{
}

void BulletManager::Initialize()
{
	// 初期化処理は特に必要ないが、明示的に呼び出す
	for (int num = 0; num < BulletNum; num++)
	{
		bullet[num] = NULL;
	}
	cooldown_timer = 0; // クールダウンタイマーをリセット
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
				bullet[num] = NULL;
			}
		}
	}
}

void BulletManager::DeleteBullet(int num)
{
	//NULLでない場合
	if (bullet[num] != NULL)
	{
		bullet[num]->DeleteBullet(num);
		bullet[num] = NULL;
	}
}

void BulletManager::Shot(const VECTOR& position, const VECTOR& direction, const float bullet_speed)
{	
	// クールダウン中は発射できない
	if (cooldown_timer > 0) {
		return;
	}

	for (int num = 0; num < BulletNum; num++)
	{
		if (bullet[num] == NULL)
		{
			bullet[num] = std::make_shared<Bullet>(position, direction,bullet_speed);
			cooldown_timer = CooldownTime; // 撃ったらクールダウン開始
			break;
		}
	}
}

const VECTOR BulletManager::GetBulletPosition(int bulletnum)
{
	if (bullet[bulletnum] != NULL) {
		return bullet[bulletnum].get()->GetPosition();
	}
	return VECTOR{ 0, -100.0f, 0 }; // NULLの場合はゼロベクトルを返す
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