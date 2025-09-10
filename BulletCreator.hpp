#pragma once

class Bullet;

class BulletCreator
{
private:

	BulletCreator(const BulletCreator&) = delete;

	BulletCreator();
	~BulletCreator();
public:
	void CreateBullet(const VECTOR& pos, const VECTOR& dir, const float& speed);	//弾を作成

	void Initialize();	//弾の初期化

	void Update();	//更新

	void Draw();	//描画

	std::shared_ptr<Bullet> GetBullet(int index) const { return bullets[index]; }

	static BulletCreator& GetBulletCreator() {

		static BulletCreator bullet_creator;

		return bullet_creator;
	}

private:

	static const int BULLET_NUM = 400;
	static constexpr float BULLET_COOLDOWN_TIME = 20; // 20フレームのクールダウン（約0.33秒）

	float bullet_cooldowntimer = 0; // 残りクールダウン時間

	std::vector<std::shared_ptr<Bullet>> bullets ;	

};
