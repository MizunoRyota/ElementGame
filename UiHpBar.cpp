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

    int hpbarReal = playerLocked->GetHp();
    if (hpbarReal < 0) hpbarReal = 0;

    if (hpbarReal > hpbar_maxhp) hpbar_maxhp = hpbarReal; // 上限更新

    if (hpbar_display > hpbarReal)
    {
        int decay_amount = static_cast<int>(DELAY_SPEED * DISPLAY_); // 減衰速度
        if (decay_amount < 1) decay_amount = 1;
        hpbar_display -= decay_amount;
        if (hpbar_display < hpbarReal) hpbar_display = hpbarReal; // 下抜け補正
    }
    else if (hpbar_display < hpbarReal)
    {
        hpbar_display = hpbarReal; // 回復は即時反映
    }
}

void UiHpBar::Draw() const
{
    auto playerLocked = player_.lock();
    if (!playerLocked || hpbar_maxhp <= 0) return;

    int hpbarReal = playerLocked->GetHp();
    if (hpbarReal < 0) hpbarReal = 0;

    float realRatio = static_cast<float>(hpbarReal) / static_cast<float>(hpbar_maxhp);
    float delayedRatio = static_cast<float>(hpbar_display) / static_cast<float>(hpbar_maxhp);
    if (realRatio < 0) realRatio = 0; if (realRatio > 1) realRatio = 1;
    if (delayedRatio < 0) delayedRatio = 0; if (delayedRatio > 1) delayedRatio = 1;

    // 背景
    DrawBox(hpbar_x - BAR_FRAME, hpbar_y - BAR_FRAME, hpbar_x + hpbar_width + BAR_FRAME, hpbar_y + hpbar_height + BAR_FRAME, Pallet::LemonYellow.GetHandle(), TRUE);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbar_width, hpbar_y + hpbar_height, Pallet::Gray.GetHandle(), TRUE);

    // 遅延バー(赤系)
    int hpbarDelayWidth = static_cast<int>(hpbar_width * delayedRatio);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbarDelayWidth, hpbar_y + hpbar_height, Pallet::Red.GetHandle(), TRUE);

    // 現在 HP (グラデーション寄り演出)
    int realWidth = static_cast<int>(hpbar_width * realRatio);
    int colorR = static_cast<int>(255 * (1.0f - realRatio));
    int colorG = static_cast<int>(220 * realRatio);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + realWidth, hpbar_y + hpbar_height, GetColor(colorR, colorG, 64), TRUE);

    // 枠
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbar_width, hpbar_y + hpbar_height, Pallet::LemonYellow.GetHandle(), FALSE);

    // 数値表示(必要なら有効化)
    //SetFontSize(40);
    //DrawFormatString(hpbar_x, hpbar_y + hpbar_height + 8, Pallet::White.GetHandle(), "HP: %d / %d", hpbarReal, hpbar_maxhp);
}
