#include "stdafx.hpp"
#include "FightOverlayUi.hpp"

FightOverlayUi::FightOverlayUi()
{
    graph_handle = LoadGraph("data/Texture/Fight.png");
    SetVisible(false);
}

FightOverlayUi::~FightOverlayUi()
{
    if (graph_handle != 0) DeleteGraph(graph_handle);
}

void FightOverlayUi::ShowForFrames(int frames)
{
    remaining_frames = frames;
    SetVisible(remaining_frames > 0);
}

void FightOverlayUi::Update()
{
    if (remaining_frames > 0)
    {
        remaining_frames--;
        if (remaining_frames <= 0)
        {
            remaining_frames = 0;
            SetVisible(false);
        }
    }
}

void FightOverlayUi::Draw() const
{
    if (!IsVisible()) return;
    DrawGraph(0, 0, graph_handle, TRUE);
}
