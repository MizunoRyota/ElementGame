#pragma once

class Skydome
{
public:
	Skydome();
	~Skydome();
	void Update();	//更新
	void Draw();	//描画
private:
	int SkydomeHandle;		//モデルハンドル
	VECTOR pos;				//ポジション
	VECTOR dir;			// 回転方向.
	// 静的定数.
	static constexpr float Scale = 0.20f;		//大きさ
};
