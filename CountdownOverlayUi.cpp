#include "stdafx.hpp"
#include "CountdownOverlayUi.hpp"

CountdownOverlayUi::CountdownOverlayUi()
{
    one_graph_handle = LoadGraph("data/Texture/CountOne.png");
    two_graph_handle = LoadGraph("data/Texture/CountTwo.png");
    three_graph_handle = LoadGraph("data/Texture/CountThree.png");
    SetVisible(false);
}

CountdownOverlayUi::~CountdownOverlayUi()
{
    if (one_graph_handle != 0) DeleteGraph(one_graph_handle);
    if (two_graph_handle != 0) DeleteGraph(two_graph_handle);
    if (three_graph_handle != 0) DeleteGraph(three_graph_handle);
}

void CountdownOverlayUi::SetSeconds(int seconds)
{
    countdown_seconds = seconds;
    SetVisible(countdown_seconds > 0);
}

void CountdownOverlayUi::Update()
{
    if (countdown_seconds <= 0)
    {
        SetVisible(false);
    }
}

void CountdownOverlayUi::Draw() const
{
    if (!IsVisible()) return;

    int handle = 0;
    if (countdown_seconds == 3) handle = three_graph_handle;
    else if (countdown_seconds == 2) handle = two_graph_handle;
    else if (countdown_seconds == 1) handle = one_graph_handle;
    else return;

    DrawGraph(0, 0, handle, TRUE);
}
