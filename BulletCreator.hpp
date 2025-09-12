#pragma once

class Bullet;

class BulletCreator
{
private:
	BulletCreator(const BulletCreator&) = delete;
	BulletCreator();
	~BulletCreator();

public:
	void CreateBullet(const VECTOR& pos, const VECTOR& dir, const float& speed);
	// 追加: ホーミング弾生成
	void CreateHomingBullet(const VECTOR& pos,
		const VECTOR& dir,
		float speed,
		std::function<VECTOR()> targetGetter,
		float homingTime,
		float turnSpeedRad);

	void Initialize();
	void Update();
	void Draw();

	std::shared_ptr<Bullet> GetBullet(int index) const { return bullets[index]; }
	int GetBulletCount() const { return static_cast<int>(bullets.size()); }

	static BulletCreator& GetBulletCreator()
	{
		static BulletCreator bullet_creator;
		return bullet_creator;
	}

private:
	static const int BULLET_NUM = 400;
	static constexpr float BULLET_COOLDOWN_TIME = 20;

	float bullet_cooldowntimer = 0;

	std::vector<std::shared_ptr<Bullet>> bullets;
};
