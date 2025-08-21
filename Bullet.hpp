#pragma once

class Bullet 
{
public:
	Bullet(const VECTOR& position,const VECTOR& direction,const float bullet_speed);
	~Bullet();

	void Initialize();
	void Update();
	void DeleteBullet(int num);
	bool CheckBulletOut();
	void PlayEffect();

	void Draw();
	//弾の生存フラグを取得
	const bool GetFlag() const { return bullet_isporn; };
	const VECTOR& GetPosition() const { return position; }


private:
	static constexpr float BulletRange = 30.0f;	//再生しているエフェクトの高さ
	static constexpr float PlayEffectSpeed = 0.025f;	//再生速度
	static constexpr float EffectScale = 0.4f;	//再生しているエフェクトの高さ
	static constexpr float EndTime = 30.0f;				//
	VECTOR direction;
	VECTOR position;
	VECTOR prev_positon;
	int effect_handle;
	int playingEffectHandle;

	bool bullet_isporn;
	float bullet_speed;
	float time;				// 時間を初期化する(定期的にエフェクトを再生するため)
	bool effect_isplay;			// エフェクトが再生中かどうかを示すフラグ
	bool effect_isend;				// エフェクトが終了したかどうかを示すフラグ

};

