#pragma once
#include "GameObject.hpp"

// スカイドーム（背景）
class Skydome : public GameObject
{
public:
	Skydome();
	~Skydome();
	// 初期化
	void Initialize()override; 

	// 更新
	void Update()override;

	// 描画
	void Draw()override;       

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
	static constexpr float SCALE = 1.0f;    // 大きさ
	static constexpr float SUNNY_MOVESPEED = 0.0002f; // 回転速度
	static constexpr float CLOUD_MOVESPEED = 0.0006f; // 回転速度

	int cloud_modelhandle; // 曇のモデルハンドル
	float sunny_direction; // 青空の回転する向き
	float cloud_direction; // 雲の回転する向き

};
