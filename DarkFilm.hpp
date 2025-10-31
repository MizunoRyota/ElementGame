#pragma once

#include "UiManager.hpp"

class Enemy;

// 画面暗転フィルム（敵の状態に応じて暗くする）
class DarkFilm : public IUiElement
{
public:
	explicit DarkFilm(const std::shared_ptr<Enemy>& enemy);

	void UpdateTitle() override {};
	void Update() override;      // 値更新
	void UpdateGameClear()override {};
	void UpdateGameOver()override {};
	void DrawTitle() const override {};
	void DrawTutorial() const override {};
	void Draw() const override;  // 描画
	void DrawGameClear() const override {};
	void DrawGameOver() const override {};
private:
	static constexpr float ALPHA_CHANGESPEED = 1.50f; // 透明度変化量

	std::weak_ptr<Enemy> enemy_; // 参照（破棄前提で弱参照）
	bool film_isblackout;        // 暗転中か
	float film_alpha;            // 現在アルファ
};
