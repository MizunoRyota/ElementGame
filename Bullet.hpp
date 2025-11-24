#pragma once

// 単発/追尾/拡散など弾本体のロジック
class Bullet
{
public:
	Bullet();
	~Bullet();

	// 基本初期化（直進など）
	void Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed, int effectTypeIndex);

	// 追尾初期化
	void InitializeHoming(const VECTOR& pos,
		const VECTOR& dir,
		float speed,
		std::function<VECTOR()> targetGetter,
		float homingTime,
		float turnSpeedRad,
		int effectTypeIndex);

	void Update();   // フレーム更新
	void Move();     // 位置更新
	void Draw();     // デバッグ描画

	void ChangeActiveTrue();  // 有効化
	void ChangeActiveFalse(); // 無効化（エフェクト停止）
	void ResetPosition();     // 位置を初期値へ
	void StopEffect();        // 再生/追尾の停止

	void InitializeBulletRadius(int effectTypeIndex); // 種類に応じた半径設定

	bool IsActive() const { return bullet_is_active; }
	const VECTOR& GetPosition() const { return bullet_position; }
	float GetBulletRadius() const { return bullet_radius; }
private:
	// ===== 当たり半径テーブル =====
	static constexpr float BULLET_FIRE_RADIUS = 0.75f;      // 直進弾
	static constexpr float BULLET_DIFFUSION_RADIUS = 0.5f;  // 拡散弾
	static constexpr float BULLET_HOMING_RADIUS = 0.5f;     // 追尾弾
	static constexpr float BULLET_SPECIAL_RADIUS = 5.0f;    // 必殺・大弾
	static constexpr float BULLET_PLAYER_RADIUS = 0.45f;    // 必殺・大弾


	// ===== 寿命関連 =====
	static constexpr float BULLET_LIFE = 60.0f;  // 生存時間(フレーム)
	static constexpr float BULLET_COUNT = 0.5f;  // 1f あたり進行量

	static constexpr int   SHADOW_DIV = 16;				// 影の分割
	static constexpr float SHADOW_TOP_HEIGHT = -0.01f;  // 影の高さ
	static constexpr float SHADOW_BOTTOM_HEIGHT = 0.05f;  // 影の高さ


	bool  bullet_is_active;   // 有効フラグ
	float bullet_speed;       // 速度スカラー
	float bullet_life;        // 残り寿命
	float bullet_radius;      // 当たり半径

	VECTOR bullet_position;       // 現在位置
	VECTOR bullet_prevposition;   // 前フレーム位置
	VECTOR bullet_direction;      // 実移動ベクトル (raw * speed)
	VECTOR bullet_rawdirection;   // 正規化された進行方向

	// --- 追尾関連 ---
	bool bullet_is_Homing = false;                // 追尾中か
	float bullet_homingTime = 0.0f;               // 残り追尾フレーム
	float bullet_turnSpeed = 0.0f;				  // フレーム毎の最大旋回量(rad)
	std::function<VECTOR()> bullet_target_getter; // ターゲット座標取得コールバック

	// エフェクト関連
	int bullet_trail_handle = -1;       // 再生中のエフェクトハンドル
	int bullet_effect_type_index = -1;  // エフェクト種別インデックス
};