#pragma once
#include "GameObject.hpp"
class Skydome : public GameObject
{
public:
	Skydome();
	~Skydome();

	void Initialize()override;	//初期化

	void Update()override;		//更新
	void Draw()override;		//描画

	// シーン別描画 (特別処理なし)
	void DrawTitle() override { Draw(); }
	void DrawGameOver() override { Draw(); }
	void DrawGameClear() override { Draw(); }

	// シーン別更新 (空実装)
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};
private:
	// 静的定数.
	static constexpr float SCALE = 0.20f;			// 大きさ
	static constexpr float MOVESPEED = 0.0004f;		// 回転の速さ

	int skydome_modelhandle;				// モデルハンドル
	VECTOR skydome_position;				// ポジション
	VECTOR skydome_dirciton;				// 回転方向.
};
