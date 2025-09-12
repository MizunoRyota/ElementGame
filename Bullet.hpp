#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed);	// 通常初期化

	// 追加: ホーミング初期化
	void InitializeHoming(const VECTOR& pos,
		const VECTOR& dir,
		float speed,
		std::function<VECTOR()> targetGetter,
		float homingTime,
		float turnSpeedRad);

	void Update();
	void Move();
	void Draw();

	void ChangeActiveTrue();
	void ChangeActiveFalse();
	void ResetPosition();

	bool IsActive() const { return bullet_isactive; }
	const VECTOR& GetPosition() const { return bullet_position; }
	static constexpr float BULLET_RADIUS = 0.3f;

private:
	static constexpr float BULLET_LIFE = 90;
	static constexpr float BULLET_COUNT = 0.5f;

	bool bullet_isactive;
	float bullet_speed;
	float bullet_life;

	VECTOR bullet_position;
	VECTOR bullet_prevposition;
	VECTOR bullet_direction;    // 実際に速度として使う(= unitDir * speed)
	VECTOR bullet_rawdirection; // 進行方向の単位ベクトル (追尾回転はこれを操作)

	// --- 追加: ホーミング関連 ---
	bool bullet_isHoming = false;
	float bullet_homingTime = 0.0f;          // 残り追尾フレーム
	float bullet_turnSpeed = 0.0f;           // 1フレーム最大回頭角(rad)
	std::function<VECTOR()> bullet_targetGetter; // 毎フレームターゲット位置取得
};
