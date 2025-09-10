#pragma once

class BulletCreator;
class GameObject;

class BulletFire
{
public:
	BulletFire();
	~BulletFire();

	void FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed);	//直線に発射

	void FireDiffusion(const VECTOR& pos, const VECTOR& dir, const float& speed);	//拡散弾を発射

	void FireVirtical(const VECTOR& pos, const VECTOR& dir, const float& speed);

	void FireHoming(const VECTOR& pos, const VECTOR& dir, const float& speed);		//ホーミング弾を発射

	void FireSpecialAttack (const VECTOR& pos, const VECTOR& dir, const float& speed);	//全方位に発射

	void FireUpdate();	//発射の更新

	VECTOR BulletRotateHorizontal(const VECTOR& dir ,float angle);		//水平向き変更

	VECTOR BulletRotateVertical(const VECTOR& dir, float angle);		//垂直向き変更

private:
	static constexpr int DIFFUSION_NUM = 5;		//拡散弾の数
	static constexpr int ALLRANGE_NUM = 30;		//全方位弾の数
	static constexpr float BULLET_COOLTIME = 10;	//

	float bullet_firecooltimer = 0;	//弾の発射クールタイム

};

