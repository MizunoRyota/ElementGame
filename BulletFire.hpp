#pragma once

class BulletCreator;
class GameObject;
class Player;        // 追加

class BulletFire
{
public:
	BulletFire();
	~BulletFire();

	void FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed);	//直線に発射

	void FireDiffusion(const VECTOR& pos, const VECTOR& dir, const float& speed);	//拡散弾を発射

	void FireVirtical(const VECTOR& pos, const VECTOR& dir, const float& speed);


	// 追加: ホーミング(ターゲット付き)
	void FireHoming(const VECTOR& pos,
		const VECTOR& dir,
		const float& speed,
		const std::shared_ptr<GameObject>& target);

	void FireSpecialAttack (const VECTOR& pos, const VECTOR& dir, const float& speed);	//全方位に発射

	void FireUpdate();	//発射の更新

	VECTOR BulletRotateHorizontal(const VECTOR& dir ,float angle);		//水平向き変更

	VECTOR BulletRotateVertical(const VECTOR& dir, float angle);		//垂直向き変更

private:
	static constexpr int DIFFUSION_NUM = 30;		//拡散弾の数
	static constexpr int ALLRANGE_NUM = 30;		//全方位弾の数
	static constexpr float BULLET_COOLTIME = 10;	//

	// 追加: ホーミングパラメータ
	static constexpr float HOMING_DURATION = 20.0f;             // 追尾するフレーム数
	static constexpr float HOMING_TURN_SPEED = DX_PI_F / 30.0f; // 1f最大回頭角(=6°)

	float bullet_firecooltimer = 0;	//弾の発射クールタイム

};

