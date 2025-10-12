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
    graph_handle = LoadDivGraph("data/Texture/Numbers.png", 11, 11, 1, 64, 64, graph_array);
}

void GameTimer::Update()
{
    if (timer_paused) return;
    timer_elapsed += DISPLAY_;
    if (timer_elapsed >= 10)
    {
        timer_elapsed = 0;
        timer_second++;
    }
    if (timer_second>=6)
    {
        timer_second = 0;
        timer_third++;
    }
    if (timer_third >= 10)
    {
        timer_third = 0;
        timer_fourth++;
    }
    timer_firest = static_cast<int>(timer_elapsed) % 60;
}

void GameTimer::UpdateGameClear()
{
    if (timer_firest_x!= SCREEN_WIDTH / HARF + OFFSET_X_SIXTY)
    {
        timer_firest_x-= TIMER_FIRST_SPEEFD;
    }
    if (timer_second_x != SCREEN_WIDTH / HARF + OFFSET_X_THIRTY)
    {
        timer_second_x-= TIMER_SECOND_SPEEFD;
    }
    if (timer_colon_x != SCREEN_WIDTH / HARF)
    {
        timer_colon_x-=TIMER_COLON_SPEEFD;
    }
    if (timer_third_x != SCREEN_WIDTH / HARF - OFFSET_X_THIRTY)
    {
        timer_third_x-=TIMER_THIRD_SPEEFD;
    }
    if (timer_fourth_x != SCREEN_WIDTH / HARF - OFFSET_X_SIXTY)
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

    DrawGraph(SCREEN_WIDTH / HARF + OFFSET_X_SIXTY, TIMER_GAMETITLE_Y, graph_array[timer_firest], true);
    DrawGraph(SCREEN_WIDTH / HARF + OFFSET_X_THIRTY, TIMER_GAMETITLE_Y, graph_array[timer_second], true);
    DrawGraph(SCREEN_WIDTH / HARF, TIMER_GAMETITLE_Y, graph_array[COLON], true);
    DrawGraph(SCREEN_WIDTH / HARF - OFFSET_X_THIRTY, TIMER_GAMETITLE_Y, graph_array[timer_third], true);
    DrawGraph(SCREEN_WIDTH / HARF - OFFSET_X_SIXTY, TIMER_GAMETITLE_Y, graph_array[timer_fourth], true);

}