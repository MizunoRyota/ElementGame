#pragma once

#include "GameObject.hpp"
class Effect;

// ステージ（床や地形）
class Stage : public GameObject
{
public:
	Stage();
	~Stage();

	void LoadJson();

	void Initialize()override;  // 初期化
	void Update()override;      // 更新
	void Draw()override;        // 描画

	// シーン別描画（背景と同様、常に描画）
	void DrawTitle() override { Draw(); }
	void DrawGameOver() override { Draw(); }
	void DrawGameClear() override { Draw(); }

	// シーン別更新（特になし）
	void UpdateGameClear() override { Update(); }
	void UpdateGameOver() override { Update(); }
	void UpdateTitle() override { Update(); }
	void UpdateTutorial() override { Update(); }

private:
	// 定数
	static constexpr float SCALE = 0.0125f;  // 大きさ
	static constexpr float STAGE_HIGHT = 0.90f; // 高さ
	static constexpr float STAGE_ROTATE_SPEED = 0.10f; // 高さ

	json stage_json_data;

};