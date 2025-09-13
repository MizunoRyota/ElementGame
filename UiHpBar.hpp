#pragma once
#include "UiManager.hpp"
#include <memory>

class Player;

// ƒvƒŒƒCƒ„[HPƒo[ UI —v‘f
class UiHpBar : public IUiElement
{
public:
    explicit UiHpBar(const std::shared_ptr<Player>& player);
    void Update(float dt) override;
    void Draw() const override;

    void SetPosition(int x, int y) { baseX_ = x; baseY_ = y; }
    void SetSize(int w, int h) { width_ = w; height_ = h; }

private:
    std::weak_ptr<Player> player_;
    int maxHp_ = 0;
    int displayHp_ = 0;         // ’x‰„•\¦—p
    static constexpr float catchUpSpeed_ = 120.0f; // 1•b‚Å120Œ¸­’Ç]

    int baseX_ = 50;
    int baseY_ = 50;
    int width_ = 600;   // ˆÈ‘O:400 -> Šg‘å
    int height_ = 40;   // ˆÈ‘O:30  -> Šg‘å
};
