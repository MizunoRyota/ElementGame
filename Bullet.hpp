#pragma once

class Bullet 
{
public:
	Bullet(const VECTOR& position,const VECTOR& direction,const float bullet_speed);
	~Bullet();

	//void Update(const VECTOR& targetpos);
	void Initialize();
	void Update();
	bool CheckBulletOut();
	void PlayEffect();

	void Draw();
	//弾の生存フラグを取得
	const bool GetFlag() const { return bullet_isporn; };
	const VECTOR& GetPosition() const { return position; }

	//bool isEmpty() const; //使ってなければtrue。mCount<0で判定
	//void die(); //弾消えます
	//const VECTOR& GetPosition() const { return mposition; }
private:
	//int mCount; //-1ならその弾は空だということにしよう。
	//bool mHoming; //追尾する？
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
	//static const float mHomingX; //角度誘導性能X
	//static const float mHomingZ; //角度誘導性能Z
	//static const int mLife; //弾寿命
	//static const float mSpeed; //弾の速度
};

