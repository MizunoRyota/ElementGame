#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed);	//弾の初期化

	void Update();	//更新

	void Move();	//移動

	void Draw();	//描画

	void ChangeActiveTrue();	//アクティブ状態をFALSEに変更

	void ChangeActiveFalse();	//アクティブ状態をTRUEに変更

	void ResetPosition();		//ポジションを初期化

	bool IsActive() const { return bullet_isactive; }	//アクティブ状態を返す

private:
	
	static constexpr float BULLET_LIFE = 90;		//弾の寿命
	static constexpr float BULLET_COUNT = 0.5f;		//寿命を進める速さ

	bool bullet_isactive;		//アクティブ状態
	float bullet_speed;			//弾の移動
	float bullet_life;			//弾の寿命

	VECTOR bullet_position;			//ポジション
	VECTOR bullet_prevposition;		//前のポジション
	VECTOR bullet_direction;		//向き

	std::shared_ptr<Bullet> bullet_next;	//弾のインスタンス

};
