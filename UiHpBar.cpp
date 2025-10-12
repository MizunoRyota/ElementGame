#include "stdafx.hpp"
#include "UiHpBar.hpp"
#include "UiManager.hpp"
#include "Player.hpp"

UiHpBar::UiHpBar(const std::shared_ptr<Player>& player)
    : player_(player)
{
    order_z = 0; // HUD 背面層

    if (auto playerLocked = player_.lock())
    {
        hpbar_maxhp = playerLocked->GetHp();
        if (hpbar_maxhp < 1) hpbar_maxhp = 1; // 0 回避
        hpbar_display = hpbar_maxhp;
    }
    else
    {
        hpbar_maxhp = 1;
        hpbar_display = 1;
    }
}

void UiHpBar::Update()
{
    auto playerLocked = player_.lock();
    if (!playerLocked) return;

    int hpbar_real = playerLocked->GetHp();
    if (hpbar_real < 0) hpbar_real = 0;

    if (hpbar_real > hpbar_maxhp) hpbar_maxhp = hpbar_real; // 上限更新

    if (hpbar_display > hpbar_real)
    {
        int decayAmount = static_cast<int>(DELAY_SPEED * DISPLAY_); // 減衰速度
        if (decayAmount < 1) decayAmount = 1;
        hpbar_display -= decayAmount;
        if (hpbar_display < hpbar_real) hpbar_display = hpbar_real; // 下抜け補正
    }
    else if (hpbar_display < hpbar_real)
    {
        hpbar_display = hpbar_real; // 回復は即時反映
    }
}

void UiHpBar::Draw() const
{
    auto playerLocked = player_.lock();
    if (!playerLocked || hpbar_maxhp <= 0) return;

    int hpbar_real = playerLocked->GetHp();
    if (hpbar_real < 0) hpbar_real = 0;

    float realRatio = static_cast<float>(hpbar_real) / static_cast<float>(hpbar_maxhp);
    float delayedRatio = static_cast<float>(hpbar_display) / static_cast<float>(hpbar_maxhp);
    if (realRatio < 0) realRatio = 0; if (realRatio > 1) realRatio = 1;
    if (delayedRatio < 0) delayedRatio = 0; if (delayedRatio > 1) delayedRatio = 1;

    // 背景
    DrawBox(hpbar_x - BAR_FRAME, hpbar_y - BAR_FRAME, hpbar_x + hpbar_width + BAR_FRAME, hpbar_y + hpbar_height + BAR_FRAME, Pallet::Aqua.GetHandle(), TRUE);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbar_width, hpbar_y + hpbar_height, Pallet::Gray.GetHandle(), TRUE);

    // 遅延バー(赤系)
    int hpbar_delay_width = static_cast<int>(hpbar_width * delayedRatio);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbar_delay_width, hpbar_y + hpbar_height, Pallet::Red.GetHandle(), TRUE);

    // 現在 HP (グラデーション寄り演出)
    int realWidth = static_cast<int>(hpbar_width * realRatio);
    int color_r = static_cast<int>(255 * (1.0f - realRatio));
    int color_g = static_cast<int>(220 * realRatio);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + realWidth, hpbar_y + hpbar_height, GetColor(color_r, color_g, 64), TRUE);

    // 枠
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbar_width, hpbar_y + hpbar_height, Pallet::White.GetHandle(), FALSE);

    // 数値表示(必要なら有効化)
    //SetFontSize(40);
    //DrawFormatString(hpbar_x, hpbar_y + hpbar_height + 8, Pallet::White.GetHandle(), "HP: %d / %d", hpbar_real, hpbar_maxhp);
}
