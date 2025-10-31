#pragma once
#include "UiManager.hpp"

// ’†‰›Æ€UI
class Reticle : public IUiElement
{
public:
	Reticle();
	~Reticle();
	void UpdateTitle() override {};
	void Update() override;      // ’lXV
	void UpdateGameClear()override {};
	void UpdateGameOver()override {};
	void Draw() const override;  // •`‰æ
	void DrawTutorial() const override {};
	void DrawTitle() const override {};
	void DrawGameOver() const override {};
	void DrawGameClear() const override {};
private:
};
