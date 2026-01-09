#pragma once
#include "UiManager.hpp"

// シーン切り替え時のUIテキストなどを描画
class Text : public IUiElement
{
public:
	Text();
	~Text();
	void UpdateTitle() override{} ;
	void Update() override;      // 値更新
	 void UpdateGameClear()override{};
	 void UpdateGameOver()override{};
	void Draw() const override;  // 描画
	void DrawTitle() const override {};
	void DrawTutorial() const override {};
	void DrawGameClear() const override {};
	void DrawGameOver() const override {};

private:
	int ready_laser_mouse;
	int ready_laser_controller;
	int not_ready_laser_mouse;
	int not_ready_laser_controller;
	int game_controller;
	int input_type;
};
