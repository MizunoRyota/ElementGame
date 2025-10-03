#pragma once
#include "UiManager.hpp"

class Text : public IUiElement
{
public:
	Text();
	~Text();
	void UpdateTitle() override{} ;
	void Update() override;      // ílçXêV
	 void UpdateGameClear()override{};
	 void UpdateGameOver()override{};
	void Draw() const override;
	void DrawTitle() const override {};  // ï`âÊ
	void DrawTutorial() const override {};
	void DrawGameClear() const override {};  // ï`âÊ
	void DrawGameOver() const override {};  // ï`âÊ
private:
	int text_graph;
};
