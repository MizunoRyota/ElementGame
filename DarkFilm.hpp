#pragma once

#include "UiManager.hpp"

class Enemy;

class DarkFilm : public IUiElement
{
public:
	explicit DarkFilm(const std::shared_ptr<Enemy>& enemy);

	void UpdateTitle() override {};
	void Update() override;      // ílçXêV
	void UpdateGameClear()override {};
	void UpdateGameOver()override {};
	void DrawTitle() const override {};  // ï`âÊ
	void DrawTutorial() const override {};
	void Draw() const override;
	void DrawGameClear() const override {};  // ï`âÊ
	void DrawGameOver() const override {};  // ï`âÊ
private:
	static constexpr float ALPHA_CHANGESPEED = 1.50f;

	std::weak_ptr<Enemy> enemy_;
	bool film_isblackout;
	float film_alpha;
};
