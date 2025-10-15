#include "stdafx.hpp"
#include "UiDashBar.hpp"
#include "Player.hpp"
#include "PlayerMove.hpp"

UiDashBar::UiDashBar(const std::shared_ptr<Player>& player)
    : player_(player)
{
    order_z = 1; // HPバーより前面に配置
    graph_handle = LoadGraph("data/Texture/Dash.png");
}

void UiDashBar::Update()
{
    // ここでは特に減衰アニメ無し。必要ならエネルギーの遅延表示を実装可
}

void UiDashBar::Draw() const
{
    auto playerLocked = player_.lock();
    if (!playerLocked) return;

    // 移動コンポーネントからダッシュエネルギー取得
    auto player_move = playerLocked->GetPlayerMove();
    float energy = player_move->GetDashEnergy();
    int maxEnergy = player_move->GetDashEnergyMax();
    int cooldown = player_move->GetDashCooldown();
    if (maxEnergy <= 0) return;

    float realRatio = static_cast<float>(energy) / static_cast<float>(maxEnergy);
    if (realRatio < 0) realRatio = 0; if (realRatio > 1) realRatio = 1;
    int realWidth = static_cast<int>(bar_width * realRatio);

    // 背景枠
    DrawBox(energy_x - 2, energy_y - 2, energy_x + bar_width + 2, energy_y + bar_height + 2, Pallet::Aqua.GetHandle(), TRUE);
    DrawBox(energy_x, energy_y, energy_x + bar_width, energy_y + bar_height, Pallet::Gray.GetHandle(), TRUE);

    // 内枠ライン
    DrawBox(energy_x, energy_y, energy_x + bar_width, energy_y + bar_height, Pallet::White.GetHandle(), FALSE);

    // バー色計算
    int barColor;
    if (cooldown > 0)
    {
        // クールタイム中: 赤(点滅風にαなしで明滅) 簡易: 残フレーム割合で明度変化
        float cdRatio = static_cast<float>(cooldown) / 60.0f; // 定数と一致想定(DASH_COOLDOWN_FRAMES)
        if (cdRatio > 1.0f) cdRatio = 1.0f;
        int r = 200;
        int g = static_cast<int>(40 + 120 * (1.0f - cdRatio)); // 時間経過で少し明るく
        int b = static_cast<int>(40 + 60 * (1.0f - cdRatio));
        barColor = GetColor(r, g, b);
    }
    else
    {
        // エネルギー残量によるグラデーション (赤 -> 黄 -> 緑)
        // 0..0.5 : 赤(255,64,32) -> 黄(255,220,64)
        // 0.5..1 : 黄(255,220,64) -> 緑(64,255,96)
        int r, g, b;
        if (realRatio < 0.5f)
        {
            float t = realRatio / 0.5f; // 0..1
            r = 255;
            g = static_cast<int>(64 + (220 - 64) * t);
            b = static_cast<int>(32 + (64 - 32) * t);
        }
        else
        {
            float t = (realRatio - 0.5f) / 0.5f; // 0..1
            r = static_cast<int>(255 + (64 - 255) * t);
            g = static_cast<int>(220 + (255 - 220) * t);
            b = static_cast<int>(64 + (96 - 64) * t);
        }
        barColor = GetColor(r, g, b);
    }

    // 実エネルギー
    DrawBox(energy_x, energy_y, energy_x + realWidth, energy_y + bar_height, barColor, TRUE);

    // クールタイム中は半透明オーバーレイで不可視化演出(任意)
    if (cooldown > 0)
    {
        // 残りクールタイム割合で斜線的マスク(簡易: 矩形で暗く)
        int alpha = 120; // 固定半透明
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawBox(energy_x, energy_y, energy_x + bar_width, energy_y + bar_height, Pallet::White.GetHandle(), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    // 数値/状態表示(必要ならコメント解除)
    //SetFontSize(22);
    //DrawFormatString(energy_x, energy_y + bar_height + 6, Pallet::White.GetHandle(), "EN:%d CD:%d", energy, cooldown);
    if ((CheckHitKey(KEY_INPUT_LSHIFT) != 0))
    {
        DrawGraphF(0, 0, graph_handle, true);
    }

}
