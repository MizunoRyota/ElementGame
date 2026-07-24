#include "stdafx.hpp"
#include "FightOverlayUi.hpp"

FightOverlayUi::FightOverlayUi()
{
    // 「FIGHT」表示用の画像を読み込む
    graph_handle = LoadGraph("data/Texture/Fight.png");
    SetVisible(false);
}

FightOverlayUi::~FightOverlayUi()
{
    // 読み込んだ画像を解放
    if (graph_handle != 0) DeleteGraph(graph_handle);
}

void FightOverlayUi::ShowForFrames(int frames)
{
    // 指定フレーム数だけ表示する
    remaining_frames = frames;
    SetVisible(remaining_frames > 0);
}

void FightOverlayUi::Update()
{
    // 残りフレームを減算し、0 になったら非表示
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
