#pragma once
class BulletCreator
{
public:
	BulletCreator();
	~BulletCreator();

	void CreateBullet();

	void Initialize();

	void Update();

	void ShotStraight(const VECTOR& pos, const VECTOR& dir, const float& speed);

	void Draw();

	std::shared_ptr<Bullet> GetBullet(int index) const { return bullets[index]; }

private:
	static const int BULLET_NUM = 100;
	static constexpr float BULLET_COOLDOWN_TIME = 20; // 20フレームのクールダウン（約0.33秒）
	float bullet_cooldowntimer = 0; // 残りクールダウン時間
	std::vector<std::shared_ptr<Bullet>> bullets;
};
