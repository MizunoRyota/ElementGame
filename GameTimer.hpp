#pragma once
#include "UiManager.hpp"

// ゲーム内経過時間を表示するUI
class GameTimer : public IUiElement
{
public:
    GameTimer();

    // 経過時間をリセット
    void Reset() { timer_elapsed = 0.0f; }

    // ポーズ / 再開
    void SetPaused(bool p) { timer_paused = p; }
     void UpdateTitle() override{};
    virtual void Update() override;      // 値更新
    virtual void UpdateGameClear()override;
    virtual void UpdateGameOver()override{};
    void Draw() const override;
    void DrawTutorial() const override {};
    void DrawTitle() const override {};  // 描画
    void DrawGameOver() const override {};  // 描画
    void DrawGameClear() const override ;  // 描画

private:
    static constexpr int NUMBERS = 11;
    static constexpr int HARF = 2;
    static constexpr int OFFSET_X_FIRST = 870;
    static constexpr int OFFSET_X_SECOND = 830;
    static constexpr int OFFSET_X_COLON = 790;
    static constexpr int OFFSET_X_THIRD = 750;
    static constexpr int OFFSET_X_FOURTH = 710;

    static constexpr int TIMER_GAMETITLE_Y = 30;
    static constexpr int TIMER_GAMECLEAR_Y = 300;

    static constexpr int COLON = 10;

    static constexpr int TIMER_FIRST_SPEEFD = 20;
    static constexpr int TIMER_SECOND_SPEEFD = 30;
    static constexpr int TIMER_COLON_SPEEFD = 20;
    static constexpr int TIMER_THIRD_SPEEFD = 30;
    static constexpr int TIMER_FOURTH_SPEEFD = 20;

    int timer_elapsed = 0; // 経過秒
    int timer_firsttime=0;
    bool  timer_paused  = false;
    int graph_array[NUMBERS];
    int timer_firest = 0;
    int timer_second = 0;
    int timer_third = 0;
    int timer_fourth = 0;

    int timer_firest_x = 0;
    int timer_second_x = 0;
    int timer_colon_x = 0;
    int timer_third_x = 0;
    int timer_fourth_x = 0;

};
