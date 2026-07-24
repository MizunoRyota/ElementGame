#include "stdafx.hpp"
#include "Bullet.hpp"
#include "BulletCreator.hpp"

BulletCreator::BulletCreator()
{
    // 弾は毎回 new せず、固定数を先に生成して使い回す（弾プール）
	for (int num = 0; num < BULLET_NUM; num++)
	{
		bullets.push_back(std::make_shared<Bullet>());
	}
}

BulletCreator::~BulletCreator() {}

/// <summary>
/// 初期化
/// </summary>
void BulletCreator::Initialize() 
{
    // 初期化時に稼働中の弾が残っていた場合は停止させる
    // ※弾プールのためゲーム再開/シーン遷移時に状態が残りうる
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->ChangeActiveFalse();
			break;
		}
	}
}
/// <summary>
/// 弾の生成
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
/// <param name="effectTypeIndex"></param>
void BulletCreator::CreateBullet(const VECTOR& pos, const VECTOR& dir, const float& speed, int effectTypeIndex)
{
    // 未使用（非アクティブ）の弾を1発だけ取得して初期化する
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Initialize(pos, dir, speed, effectTypeIndex);
			break;
		}
	}
}
/// <summary>
/// ホーミング弾の生成
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="speed"></param>
/// <param name="targetGetter"></param>
/// <param name="homingDuration"></param>
/// <param name="turnSpeedRad"></param>
/// <param name="effectTypeIndex"></param>
void BulletCreator::CreateHomingBullet(const VECTOR& pos, const VECTOR& dir, const float& speed, std::function<VECTOR()> targetGetter, float homingDuration, float turnSpeedRad, int effectTypeIndex)
{
    // 追尾弾版：ターゲット取得関数と追尾パラメータを渡して初期化する
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->InitializeHoming(pos, dir, speed, std::move(targetGetter), homingDuration, turnSpeedRad, effectTypeIndex);
			break;
		}
	}
}

/// <summary>
/// 更新
/// </summary>
void BulletCreator::Update()
{
    // 稼働中の弾だけ更新する（非アクティブはプール待機）
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Update();
		}
	}
}
/// <summary>
/// 描画
/// </summary>
void BulletCreator::Draw()
{
    // 稼働中の弾だけ描画する
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Draw();
		}
	}
}
/// <summary>
/// 弾エフェクトの停止（全弾）
/// </summary>
void BulletCreator::StopBulletEffect()
{
    // 外部都合（シーン終了/ゲーム終了など）で弾エフェクト停止条件を強制チェックする
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->StopEffect();
		}
	}
}