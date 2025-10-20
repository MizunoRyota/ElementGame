#include "stdafx.hpp"
#include "GameTimer.hpp"
#include "UiManager.hpp"

GameTimer::GameTimer()
{
    timer_firest_x = SCREEN_WIDTH;
    timer_second_x = SCREEN_WIDTH;
    timer_colon_x = SCREEN_WIDTH;
    timer_third_x = SCREEN_WIDTH;
    timer_fourth_x = SCREEN_WIDTH;
    timer_firsttime = GetNowCount();
    graph_handle = LoadDivGraph("data/Texture/Numbers.png", 11, 11, 1, 64, 64, graph_array);
}

void GameTimer::Update()
{
    if (timer_paused) return;

    const int now = GetNowCount();
    timer_elapsed = now - timer_firsttime;

    // 経過時間を正しく「分・秒・各桁」に分解
    const int totalSeconds = static_cast<int>(timer_elapsed / 1000);
    const int seconds = totalSeconds % 60;
    const int minutes = (totalSeconds / 60) % 100; // 99分まで表示

    // 右から: [sec_units][sec_tens] : [min_units][min_tens]
    timer_firest  = seconds % 10;             // 秒(1の位)
    timer_second  = (seconds / 10) % 10;      // 秒(10の位)
    timer_third   = minutes % 10;             // 分(1の位)
    timer_fourth  = (minutes / 10) % 10;      // 分(10の位)
}

void GameTimer::UpdateGameClear()
{
    if (timer_firest_x!= SCREEN_WIDTH / HARF + OFFSET_X_FIRST)
    {
        timer_firest_x-= TIMER_FIRST_SPEEFD;
    }
    if (timer_second_x != SCREEN_WIDTH / HARF + OFFSET_X_SECOND)
    {
        timer_second_x-= TIMER_SECOND_SPEEFD;
    }
    if (timer_colon_x != SCREEN_WIDTH / HARF + OFFSET_X_COLON)
    {
        timer_colon_x-=TIMER_COLON_SPEEFD;
    }
    if (timer_third_x != SCREEN_WIDTH / HARF - OFFSET_X_THIRD)
    {
        timer_third_x-=TIMER_THIRD_SPEEFD;
    }
    if (timer_fourth_x != SCREEN_WIDTH / HARF - OFFSET_X_FOURTH)
    {
        timer_fourth_x-= TIMER_FOURTH_SPEEFD;
    }
}

void GameTimer::DrawGameClear() const
{
    DrawGraph(timer_firest_x, TIMER_GAMECLEAR_Y, graph_array[timer_firest], true);
    DrawGraph(timer_second_x, TIMER_GAMECLEAR_Y, graph_array[timer_second], true);
    DrawGraph(timer_colon_x, TIMER_GAMECLEAR_Y, graph_array[COLON], true);
    DrawGraph(timer_third_x, TIMER_GAMECLEAR_Y, graph_array[timer_third], true);
    DrawGraph(timer_fourth_x, TIMER_GAMECLEAR_Y, graph_array[timer_fourth], true);
}

void GameTimer::Draw() const
{
    if (!uielement_visible) return;

    DrawGraph((SCREEN_WIDTH / HARF) + OFFSET_X_FIRST,  TIMER_GAMETITLE_Y, graph_array[timer_firest],  true);
    DrawGraph((SCREEN_WIDTH / HARF) + OFFSET_X_SECOND, TIMER_GAMETITLE_Y, graph_array[timer_second], true);
    DrawGraph((SCREEN_WIDTH / HARF) + OFFSET_X_COLON,  TIMER_GAMETITLE_Y, graph_array[COLON],        true);
    DrawGraph((SCREEN_WIDTH / HARF) + OFFSET_X_THIRD,  TIMER_GAMETITLE_Y, graph_array[timer_third],  true);
    DrawGraph((SCREEN_WIDTH / HARF) + OFFSET_X_FOURTH, TIMER_GAMETITLE_Y, graph_array[timer_fourth], true);
}