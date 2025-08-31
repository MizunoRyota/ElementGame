#pragma once
#include "GameObject.hpp"
class Skydome : public GameObject
{
public:
	Skydome();
	~Skydome();

	void Initialize()override;

	void Update()override;	//更新
	void Draw()override;	//描画
private:
	// 静的定数.
	static constexpr float SCALE = 0.20f;		//大きさ
	static constexpr float MOVESPEED = 0.0004f;		//大きさ

	int skydome_modelhandle;		//モデルハンドル
	VECTOR skydome_position;				//ポジション
	VECTOR skydome_dirciton;			// 回転方向.
};
