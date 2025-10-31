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
	int text_graph; // 使用する画像ハンドル
};
