#pragma once
#include "UiManager.hpp"

class Reticle : public IUiElement
{
public:
    Reticle();
    ~Reticle();
    void UpdateTitle() override {};
    void Update() override;      // ílçXêV
    void UpdateGameClear()override {};
    void UpdateGameOver()override {};
    void Draw() const override;
    void DrawTutorial() const override {};
    void DrawTitle() const override {};  // ï`âÊ
    void DrawGameOver() const override {};  // ï`âÊ
    void DrawGameClear() const override {};  // ï`âÊ
private:

};
