#pragma once
#include "UiManager.hpp"
#include <memory>

class Player;

// ダッシュ(スタミナ/エネルギー)表示バー UI
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
    std::weak_ptr<Player> player_; // 参照: プレイヤー

    // 表示レイアウト
    int energy_x = 50;      // 左上 X 位置
    int energy_y = 950;     // 左上 Y 位置
    int bar_width = 300;    // バー全幅
    int bar_height = 20;    // バー高さ
};
