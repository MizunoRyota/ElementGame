#pragma once
#include "UiManager.hpp"
#include <memory>

class Player;

// ダッシュ(スタミナ/エネルギー)状態を示すバー UI
class UiDashBar : public IUiElement
{
public:

    explicit UiDashBar(const std::shared_ptr<Player>& player); // プレイヤー参照で初期化
    ~UiDashBar();

    void UpdateTitle() override {};
    void Update() override;      // 値更新
    void UpdateGameClear()override {};
    void UpdateGameOver()override {};
    void Draw() const override; // 描画
    void DrawTitle() const override {};  // 描画
    void DrawTutorial() const override {};
    void DrawGameOver() const override {};  // 描画
    void DrawGameClear() const override {};  // 描画
    void SetOffset(int x, int y) { energy_x = x; energy_y = y; }            // 画面配置
    void SetSize(int w, int h) { bar_width = w; bar_height = h; }           // バーサイズ

private:
    static constexpr float DASH_COOLDOWN_DURATION = 60.0f;  // ダッシュクールタイム フレーム数
    static constexpr int COOLDOWN_OVERLAY_ALPHA = 120;      // クールタイム時のオーバーレイ透明度
    static constexpr int ENERGY_MIDPOINT_RATIO = 50;        // エネルギー色変化の中間点（%）

    // 色定義: RGB
    static constexpr int COLOR_RED_R = 255;
    static constexpr int COLOR_RED_G = 64;
    static constexpr int COLOR_RED_B = 32;

    static constexpr int COLOR_YELLOW_R = 255;
    static constexpr int COLOR_YELLOW_G = 220;
    static constexpr int COLOR_YELLOW_B = 64;

    static constexpr int COLOR_GREEN_R = 64;
    static constexpr int COLOR_GREEN_G = 255;
    static constexpr int COLOR_GREEN_B = 96;

    static constexpr int COOLDOWN_COLOR_R = 200;
    static constexpr int COOLDOWN_COLOR_BASE_G = 40;
    static constexpr int COOLDOWN_COLOR_DELTA_G = 120;
    static constexpr int COOLDOWN_COLOR_BASE_B = 40;
    static constexpr int COOLDOWN_COLOR_DELTA_B = 60;

    std::weak_ptr<Player> player_; // 参照: プレイヤー

    // 表示レイアウト
    int energy_x = 50;      // エネルギー X 位置
    int energy_y = 950;     // エネルギー Y 位置
    int bar_width = 300;    // バー全幅
    int bar_height = 35;    // バー高さ

    int graph_handle = -1;  // テクスチャハンドル
};
