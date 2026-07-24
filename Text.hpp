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

	int ready_laser_mouse;			//レーザーが発射可能かどうか（マウス用）
	int ready_laser_controller;		//レーザーが発射可能かどうか（コントローラー用）
	int not_ready_laser_mouse;		//レーザーが使えなくなっっているか（マウス用）
	int not_ready_laser_controller; //レーザーが使えなくなっっているか（コントローラー用）
	int game_controller;			//コントローラーハンドル
	int input_type;					//入力ハンドル
};
