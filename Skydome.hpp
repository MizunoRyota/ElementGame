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
	void UpdateGameClear() override { Update(); }
	void UpdateGameOver() override { Update(); }
	void UpdateTutorial() override { Update(); }
	void UpdateTitle() override { Update(); }
private:
	// 定数
	static constexpr float SCALE = 0.40f;    // 大きさ
	static constexpr float SUNNY_MOVESPEED = 0.0002f; // 回転速度
	static constexpr float CLOUD_MOVESPEED = 0.0006f; // 回転速度

	int cloud_modelhandle;   // モデル
	float sunny_direction;
	float cloud_direction;

};
