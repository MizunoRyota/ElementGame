#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed, int effectTypeIndex); // 通常初期化
	// ホーミング初期化
	void InitializeHoming(const VECTOR& pos,
		const VECTOR& dir,
		float speed,
		std::function<VECTOR()> targetGetter,
		float homingTime,
		float turnSpeedRad,
		int effectTypeIndex);

	void Update();   // フレーム更新
	void Move();     // 位置更新
	void Draw();     // 描画(デバッグ)

	void ChangeActiveTrue();  // 有効化
	void ChangeActiveFalse(); // 無効化＋エフェクト停止
	void ResetPosition();     // 原点へリセット
	void StopEffect();        // 寿命/衝突で停止

	void InitializeBulletRadius(int effectTypeIndex); // 種別に応じ半径設定

	bool IsActive() const { return bullet_isactive; }
	const VECTOR& GetPosition() const { return bullet_position; }
	float GetBulletRadius() const { return bullet_radius; }
private:
	// ===== 半径テーブル =====
	static constexpr float BULLET_FIRE_RADIUS = 0.45f;      // 直進弾
	static constexpr float BULLET_DIFFUSION_RADIUS = 0.5f;  // 拡散弾
	static constexpr float BULLET_HOMING_RADIUS = 0.2f;     // 追尾弾
	static constexpr float BULLET_SPECIAL_RADIUS = 3.0f;    // 特殊落下弾

	// ===== 寿命制御 =====
	static constexpr float BULLET_LIFE = 60.0f;  // 基本寿命(フレーム)
	static constexpr float BULLET_COUNT = 0.5f;  // 1f 減算量

	static constexpr int SHADOW_DIV = 16;  // 影の半径
	static constexpr float SHADOW_TOP_HEIGHT = -0.1f;  // 影の半径


	bool  bullet_isactive;   // 有効か
	float bullet_speed;      // 速度スカラー
	float bullet_life;       // 残寿命
	float bullet_radius;     // 判定半径

	VECTOR bullet_position;      // 現在位置
	VECTOR bullet_prevposition;  // 前フレーム位置(未使用可)
	VECTOR bullet_direction;     // 実移動ベクトル (raw * speed)
	VECTOR bullet_rawdirection;  // 正規化方向ベクトル

	// --- ホーミング関連 ---
	bool bullet_isHoming = false;              // 追尾中か
	float bullet_homingTime = 0.0f;            // 残追尾フレーム
	float bullet_turnSpeed = 0.0f;             // 最大回頭角/フレーム(rad)
	std::function<VECTOR()> bullet_target_getter; // ターゲット位置取得関数

	// エフェクト関連
	int bullet_trail_handle = -1;       // 再生中ハンドル
	int bullet_effect_type_index = -1;  // エフェクト種別インデックス
};