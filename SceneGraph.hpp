#pragma once
#include "UiManager.hpp"

class SceneGraph : public IUiElement
{
public:
	SceneGraph();
	~SceneGraph();
     void UpdateTitle() override { Update(); };
     void Update() override;      // ílçXêV
     void UpdateGameClear()override { Update(); };
     void UpdateGameOver()override { Update(); }
	void Draw() const override;
    void DrawTitle() const override ;  // ï`âÊ
    void DrawTutorial() const override;
    void DrawGameOver() const override ;  // ï`âÊ
    void DrawGameClear() const override ;  // ï`âÊ
private:

    static constexpr float UP_SPEED = 1.0f;
    static constexpr float DOWN_SPEED = 0.75f;
    bool button_isdown;
    float button_pos_y;

    int title_graph;
    int titlebutton_graph;
    int tutorial_graph;
    int tutorialbutton_graph;
    int gameover_graph;
    int gameclear_graph;
};