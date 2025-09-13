#pragma once
#include "UiManager.hpp"
#include <memory>

class Enemy;

// 敵HPバー UI 要素 (画面右上表示)
class UiEnemyHpBar : public IUiElement
{
public:
    explicit UiEnemyHpBar(const std::shared_ptr<Enemy>& enemy);
    void Update(float dt) override;
    void Draw() const override;

    void SetOffset(int x, int y) { offsetX_ = x; offsetY_ = y; }
    void SetSize(int w, int h) { width_ = w; height_ = h; }

private:
    std::weak_ptr<Enemy> enemy_;
    int maxHp_ = 0;
    int displayHp_ = 0;
    static constexpr float catchUpSpeed_ = 10.0f; // 遅延追従速度

    // 右上アンカー用
    int offsetX_ = 50; // 右端からのオフセット
    int offsetY_ = 50; // 上から
    int width_ = 600;  // 以前:400 -> 拡大
    int height_ = 40;  // 以前:30  -> 拡大
};
