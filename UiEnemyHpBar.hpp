#pragma once
#include "UiManager.hpp"

class Enemy;

// 敵 HP バー (画面右上表示)
class UiEnemyHpBar : public IUiElement
{
public:
    explicit UiEnemyHpBar(const std::shared_ptr<Enemy>& enemy); // 敵参照
    void UpdateTitle() override {};
    void Update() override;      // 値更新
    void UpdateGameClear()override {};
    void UpdateGameOver()override {};
    void Draw() const override; // 描画
    void DrawTitle() const override {};  // 描画
    void DrawTutorial() const override {};
    void DrawGameOver() const override {};  // 描画
    void DrawGameClear() const override {};  // 描画
    void SetOffset(int x, int y) { offset_x = x; offset_y = y; } // 右上オフセット
    void SetSize(int w, int h) { hpbar_width = w; hpbar_height = h; } // バーサイズ

private:
    std::weak_ptr<Enemy> enemy_; // HP 参照
    int hpbar_maxhp = 0;         // 最大 HP
    int hpbar_display = 0;       // 遅延表示 HP
    static constexpr float DELAY_SPEED = 10.0f; // 減衰速度

    // レイアウト (右上基準: 画面幅 - offset_x - width)
    int offset_x = 50; // 右端からの距離
    int offset_y = 50; // 上端からの距離
    int hpbar_width = 750;  // 幅
    int hpbar_height = 50;  // 高さ
};
