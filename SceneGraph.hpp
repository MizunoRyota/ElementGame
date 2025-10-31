#pragma once
#include "UiManager.hpp"

// タイトル/チュートリアル/ゲームオーバー/クリアの各画面UI
class SceneGraph : public IUiElement
{
public:
	SceneGraph();
	~SceneGraph();
	void UpdateTitle() override { Update(); };
	void Update() override;      // 値更新
	void UpdateGameClear()override { Update(); };
	void UpdateGameOver()override { Update(); }
	void Draw() const override;  // 描画
	void DrawTitle() const override ;
	void DrawTutorial() const override;
	void DrawGameOver() const override ;
	void DrawGameClear() const override ;
private:

	static constexpr float UP_SPEED = 1.0f;   // ボタン上移動速度
	static constexpr float DOWN_SPEED = 0.75f;// ボタン下移動速度
	bool button_isdown;   // 押下状態
	float button_pos_y;   // Y位置

	int title_graph;
	int titlebutton_graph;
	int tutorial_graph;
	int tutorialbutton_graph;
	int gameover_graph;
	int gameclear_graph;
};