#pragma once
#include "UiManager.hpp"

class FightOverlayUi final : public IUiElement
{
public:
    FightOverlayUi();
    ~FightOverlayUi();

    void UpdateTitle() override {}
    void Update() override;
    void UpdateGameClear() override {}
    void UpdateGameOver() override {}

    void DrawTitle() const override {}
    void DrawTutorial() const override {}
    void Draw() const override;
    void DrawGameOver() const override {}
    void DrawGameClear() const override {}

    void ShowForFrames(int frames);

private:
    int remaining_frames = 0;
};
