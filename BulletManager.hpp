#pragma once
#include <memory>
class Bullet;
class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	void Shot(const VECTOR& position, const VECTOR& direction);
	void Update();
	void Draw();
	//弾の生存フラグを取得
	const VECTOR GetBulletPosition();
private:
	static constexpr int BulletNum = 50;
	static constexpr float CooldownTime = 20; // 20フレームのクールダウン（約0.33秒）
	float cooldown_timer = 0; // 残りクールダウン時間
	std::shared_ptr<Bullet>bullet[BulletNum];
public:
};

