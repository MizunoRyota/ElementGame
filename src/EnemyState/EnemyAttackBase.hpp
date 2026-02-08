#pragma once

class BulletFire;

class EnemyAttackBase
{
public:
	EnemyAttackBase();
	~EnemyAttackBase();

protected:
	static constexpr float BULLET_HIGHT = -1.0f;               // 発射位置オフセット(Yが負で手前になる環境向け)
	std::shared_ptr<BulletFire> enemy_bullet = std::make_shared<BulletFire>();// 弾生成
};
