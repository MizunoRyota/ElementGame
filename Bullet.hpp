#pragma once

class Bullet 
{
public:
	Bullet(const VECTOR& position,const VECTOR& direction);
	~Bullet();

	//void Update(const VECTOR& targetpos);
	void Initialize();
	void Update();
	bool CheckBulletOut();

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
	static constexpr float BulletSpeed = 0.5f;
	static constexpr float BulletRange = 30.0f;	//再生しているエフェクトの高さ

	VECTOR direction;
	VECTOR position;
	VECTOR prev_positon;
	bool bullet_isporn;
	//static const float mHomingX; //角度誘導性能X
	//static const float mHomingZ; //角度誘導性能Z
	//static const int mLife; //弾寿命
	//static const float mSpeed; //弾の速度
};

