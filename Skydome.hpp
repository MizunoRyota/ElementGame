#pragma once
#include "GameObject.hpp"

// スカイドーム（背景）
class Skydome : public GameObject
{
public:
	Skydome();
	~Skydome();

	void Initialize()override; // 初期化
	void Update()override;     // 更新
	void Draw()override;       // 描画

	// シーン別描画（背景は常に描く）
	void DrawTitle() override { Draw(); }
	void DrawGameOver() override { Draw(); }
	void DrawGameClear() override { Draw(); }

	// シーン別更新（特になし）
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};
private:
	// 定数
	static constexpr float SCALE = 0.40f;    // 大きさ
	static constexpr float MOVESPEED = 0.0004f; // 回転速度

	int skydome_modelhandle;   // モデル
	VECTOR skydome_position;   // 位置
	VECTOR skydome_dirciton;   // 回転
};
