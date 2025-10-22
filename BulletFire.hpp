#pragma once

#include <vector>

class BulletCreator;
class GameObject;
class Player;        // 追加

class BulletFire
{
public:
	BulletFire();
	~BulletFire();

	void FirePlayer(const VECTOR& pos, const VECTOR& dir, const float& speed);

	void FireStraight(const VECTOR& pos, const VECTOR& dir, const float& speed); //直線に発射

	void FireDiffusion(const VECTOR& pos, const VECTOR& dir, const float& speed); //拡散弾を発射

	void FireVirtical(const VECTOR& pos, const VECTOR& dir, const float& speed);

	//void FireRotate();

	// 追加: ホーミング(ターゲット付き)
	void FireHoming(const VECTOR& pos,
		const VECTOR& dir,
		const float& speed,
		const std::shared_ptr<GameObject>& target);

	void FireSpecialAttack (const VECTOR& pos, const VECTOR& dir, const float& speed); //全方位に発射

	void FireUpdate(); //発射の更新

	VECTOR BulletRotateHorizontal(const VECTOR& dir ,float angle); //水平向き変更

	VECTOR BulletRotateVertical(const VECTOR& dir, float angle); //垂直向き変更

	// 追加: エフェクトフレーバー
	enum class EffectFlavor
	{
		Fire = 0,
		Water = 1,
		Wind = 2,
		Special = 3,
		Hit = 4,
		FireGround = 5,
		PlayerAttack = 14,
	};

	// エフェクトインデックス変換ヘルパー
	static int ToEffectIndex(EffectFlavor f);

private:

	static constexpr int DIFFUSION_NUM = 5; //拡散弾の数
	static constexpr int DIFFUSION_OFFSET = 2; //拡散弾の最初の弾のずれ
	static constexpr int DIFFUSION_RADIUS = 30; //拡散弾の角度

	static constexpr int ALLRANGE_NUM = 30; //全方位弾の数
	static constexpr float BULLET_COOLTIME = 10; //
	static constexpr int VERTICAL_NUM = 30;
	static constexpr int HORIZONTAL_NUM = 20;
	// 追加: ホーミングパラメータ
	static constexpr float HOMING_DURATION = 20.0f;             // 追尾するフレーム数
	static constexpr float HOMING_TURN_SPEED = DX_PI_F / 30.0f; // 1f最大回頭角(=6°)

	// マーカー関連パラメータ
	static constexpr float MARKER_HEIGHT = 3.0f; // 円錐の高さ
	static constexpr float MARKER_RADIUS = 1.2f; // 底面半径
	static constexpr int   MARKER_SLICES = 16;   // 分割数

	//必殺技の弾
	static constexpr float RING_RADIUS = 20;  // 最大半径
	static constexpr float DROP_HEIGHT = 30;  // 上空高さ
	static constexpr int   INNER_RINGS = 2;  // 同心円数
	static constexpr float RADIUS_STEP = 8.0f;// 半径減少ステップ
	static constexpr float MARKER_LIFE = 60.0f; // マーカー寿命

	float bullet_firecooltimer = 0; //弾の発射クールタイム

};


