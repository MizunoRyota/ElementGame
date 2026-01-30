#pragma once
#include "UiManager.hpp"

class Player;

// プレイヤー HP バー UI 要素
class UiHpBar : public IUiElement
{
public:
    explicit UiHpBar(const std::shared_ptr<Player>& player); // プレイヤー参照で初期化
    void UpdateTitle() override {};
    void Update() override;      // 値更新
    void UpdateGameClear()override {};
    void UpdateGameOver()override {};
    void Draw() const override; // 描画
    void DrawTitle() const override {};  // 描画
    void DrawTutorial() const override {};
    void DrawGameOver() const override {};  // 描画
    void DrawGameClear() const override {};  // 描画
    void SetPosition(int x, int y) { hpbar_x = x; hpbar_y = y; } // 位置変更
    void SetSize(int w, int h) { hpbar_width = w; hpbar_height = h; } // サイズ変更

private:
    static constexpr int DELAY_SPEED = 10; // 減衰速度

    static constexpr int G_DECREASE_RAITO = 50; // 減衰速度
    static constexpr int B_DECREASE_RAITO = 180; // 減衰速度

    static constexpr int BAR_FRAME = 2; // 減衰速度
    static constexpr int BAR_R = 200; // 固定赤系ベース（好みに応じてグラデ調整可）

    int hpbar_maxhp = 0;           // 最大 HP(動的調整可)
    int hpbar_display = 0;         // 遅延表示用 HP

    // レイアウト
    int hpbar_x = 50;
    int hpbar_y = 900;
    int hpbar_width = 300;  // バー幅
    int hpbar_height = 40;  // バー高さ

    std::weak_ptr<Player> player_; // HP 取得用参照
};
