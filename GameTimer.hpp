#pragma once
#include "UiManager.hpp"

// 経過時間を表示するUI
class GameTimer : public IUiElement
{
public:
	GameTimer();
	~GameTimer();
	void Reset() { timer_elapsed = 0; } // 経過フレームをリセット

	void SetPaused(bool p) { timer_paused = p; } // 一時停止/解除
	void UpdateTitle() override{};
	virtual void Update() override;      // 値更新
	virtual void UpdateGameClear()override;
	virtual void UpdateGameOver()override{};
	void Draw() const override;          // 表示
	void DrawTutorial() const override {};
	void DrawTitle() const override {};
	void DrawGameOver() const override {};
	void DrawGameClear() const override ; // ゲームクリア時の描画

private:
	static constexpr int NUMBERS = 11; // 表示する数字の個数
	static constexpr int HARF = 2; // 不明
	static constexpr int OFFSET_X_FIRST = 870; // 最初の数字のXオフセット
	static constexpr int OFFSET_X_SECOND = 830; // 二番目の数字のXオフセット
	static constexpr int OFFSET_X_COLON = 790; // コロンのXオフセット
	static constexpr int OFFSET_X_THIRD = 750; // 三番目の数字のXオフセット
	static constexpr int OFFSET_X_FOURTH = 710; // 四番目の数字のXオフセット

	static constexpr int TIMER_GAMETITLE_Y = 30; // タイトル時のYオフセット
	static constexpr int TIMER_GAMECLEAR_Y = 300; // ゲームクリア時のYオフセット

	static constexpr int COLON = 10; // 不明

	static constexpr int TIMER_FIRST_SPEEFD = 40; // 最初の数字のスピード
	static constexpr int TIMER_SECOND_SPEEFD = 35; // 二番目の数字のスピード
	static constexpr int TIMER_COLON_SPEEFD = 30; // コロンのスピード
	static constexpr int TIMER_THIRD_SPEEFD = 25; // 三番目の数字のスピード
	static constexpr int TIMER_FOURTH_SPEEFD = 20; // 四番目の数字のスピード

	int timer_elapsed = 0; // 経過秒
	int timer_firsttime=0; // 不明
	bool  timer_paused  = false; // ポーズ中かどうか
	int graph_array[NUMBERS]; // 不明
	int timer_first = 0; // 最初の数字
	int timer_second = 0; // 二番目の数字
	int timer_third = 0; // 三番目の数字
	int timer_fourth = 0; // 四番目の数字

	int timer_first_x = 0; // 最初の数字のX位置
	int timer_second_x = 0; // 二番目の数字のX位置
	int timer_colon_x = 0; // コロンのX位置
	int timer_third_x = 0; // 三番目の数字のX位置
	int timer_fourth_x = 0; // 四番目の数字のX位置
};
