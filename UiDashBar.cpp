#include "stdafx.hpp"
#include "UiDashBar.hpp"
#include "Player.hpp"
#include "PlayerMove.hpp"

UiDashBar::UiDashBar(const std::shared_ptr<Player>& player)
    : player_(player)
{
    order_z = 0; // HPバーより前面に配置
    graph_handle = LoadGraph("data/Texture/Dash.png");
}

UiDashBar::~UiDashBar()
{
    // ここでは特に減衰アニメ無し。必要ならエネルギーの遅延表示を実装可
    DeleteGraph(graph_handle);
}

void UiDashBar::Update()
{

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
    DrawBox(energy_x, energy_y, energy_x + bar_width, energy_y + bar_height, Pallet::Gray.GetHandle(), TRUE);

    // 内枠ライン
    DrawBox(energy_x, energy_y, energy_x + bar_width, energy_y + bar_height, Pallet::White.GetHandle(), FALSE);

    // バー色計算
    int barColor;
    if (cooldown > 0)
    {
        // クールタイム中: 赤(点滅風にαなしで明滅) 簡易: 残フレーム割合で明度変化
        float cdRatio = static_cast<float>(cooldown) / DASH_COOLDOWN_DURATION;
        if (cdRatio > 1.0f) cdRatio = 1.0f;
        int r = COOLDOWN_COLOR_R;
        int g = static_cast<int>(COOLDOWN_COLOR_BASE_G + COOLDOWN_COLOR_DELTA_G * (1.0f - cdRatio));
        int b = static_cast<int>(COOLDOWN_COLOR_BASE_B + COOLDOWN_COLOR_DELTA_B * (1.0f - cdRatio));
        barColor = GetColor(r, g, b);
    }
    else
    {
        // エネルギー残量によるグラデーション (赤 -> 黄 -> 緑)
        // 0..0.5 : 赤 -> 黄
        // 0.5..1 : 黄 -> 緑
        int r, g, b;
        constexpr float MidPosition = ENERGY_MIDPOINT_RATIO / 100.0f;
        if (realRatio < MidPosition)
        {
            float t = realRatio / MidPosition; // 0..1
            r = COLOR_RED_R;
            g = static_cast<int>(COLOR_RED_G + (COLOR_YELLOW_G - COLOR_RED_G) * t);
            b = static_cast<int>(COLOR_RED_B + (COLOR_YELLOW_B - COLOR_RED_B) * t);
        }
        else
        {
            float t = (realRatio - MidPosition) / (1.0f - MidPosition); // 0..1
            r = static_cast<int>(COLOR_YELLOW_R + (COLOR_GREEN_R - COLOR_YELLOW_R) * t);
            g = static_cast<int>(COLOR_YELLOW_G + (COLOR_GREEN_G - COLOR_YELLOW_G) * t);
            b = static_cast<int>(COLOR_YELLOW_B + (COLOR_GREEN_B - COLOR_YELLOW_B) * t);
        }
        barColor = GetColor(r, g, b);
    }

    // 実エネルギー
    DrawBox(energy_x, energy_y, energy_x + realWidth, energy_y + bar_height, barColor, TRUE);

    // クールタイム中は半透明オーバーレイで不可視化演出(任意)
    if (cooldown > 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, COOLDOWN_OVERLAY_ALPHA);
        DrawBox(energy_x, energy_y, energy_x + bar_width, energy_y + bar_height, Pallet::White.GetHandle(), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    if ((CheckHitKey(KEY_INPUT_LSHIFT) != 0) || ObjectAccessor::GetObjectAccessor().GetIsInputLeftShoulder())
    {
        DrawGraphF(0, 0, graph_handle, true);
    }

}
