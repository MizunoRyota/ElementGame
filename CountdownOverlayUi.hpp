#pragma once
#include "UiManager.hpp"

class CountdownOverlayUi final : public IUiElement
{
public:
    CountdownOverlayUi();
    ~CountdownOverlayUi();

    void UpdateTitle() override {}
    void Update() override;
    void UpdateGameClear() override {}
    void UpdateGameOver() override {}

    void DrawTitle() const override {}
    void DrawTutorial() const override {}
    void Draw() const override;
    void DrawGameOver() const override {}
    void DrawGameClear() const override {}

    void SetSeconds(int seconds);

private:
    int one_graph_handle = 0;
    int two_graph_handle = 0;
    int three_graph_handle = 0;

    int countdown_seconds = 0;
};
