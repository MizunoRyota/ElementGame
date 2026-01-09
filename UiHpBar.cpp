#include "stdafx.hpp"
#include "UiHpBar.hpp"
#include "UiManager.hpp"
#include "Player.hpp"

UiHpBar::UiHpBar(const std::shared_ptr<Player>& player)
    : player_(player)
{
    order_z = 0; // HUD îwñ ëw

    if (auto playerLocked = player_.lock())
    {
        hpbar_maxhp = playerLocked->GetHp();
        if (hpbar_maxhp < 1) hpbar_maxhp = 1; // 0 âÒî
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

    if (hpbarReal > hpbar_maxhp) hpbar_maxhp = hpbarReal; // è„å¿çXêV

    if (hpbar_display > hpbarReal)
    {
        int decayAmount = static_cast<int>(DELAY_SPEED * DISPLAY_); // å∏êäë¨ìx
        if (decayAmount < 1) decayAmount = 1;
        hpbar_display -= decayAmount;
        if (hpbar_display < hpbarReal) hpbar_display = hpbarReal; // â∫î≤ÇØï‚ê≥
    }
    else if (hpbar_display < hpbarReal)
    {
        hpbar_display = hpbarReal; // âÒïúÇÕë¶éûîΩâf
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

    // îwåi
    DrawBox(hpbar_x - BAR_FRAME, hpbar_y - BAR_FRAME, hpbar_x + hpbar_width + BAR_FRAME, hpbar_y + hpbar_height + BAR_FRAME, Pallet::LemonYellow.GetHandle(), TRUE);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbar_width, hpbar_y + hpbar_height, Pallet::Gray.GetHandle(), TRUE);

    // íxâÑÉoÅ[(ê‘ån)
    int hpbarDelayWidth = static_cast<int>(hpbar_width * delayedRatio);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbarDelayWidth, hpbar_y + hpbar_height, Pallet::Red.GetHandle(), TRUE);

    // åªç› HP (ÉOÉâÉfÅ[ÉVÉáÉìäÒÇËââèo)
    int realWidth = static_cast<int>(hpbar_width * realRatio);
    int colorR = static_cast<int>(255 * (1.0f - realRatio));
    int colorG = static_cast<int>(255 * realRatio);
    DrawBox(hpbar_x, hpbar_y, hpbar_x + realWidth, hpbar_y + hpbar_height, GetColor(colorR, colorG, 64), TRUE);

    // òg
    DrawBox(hpbar_x, hpbar_y, hpbar_x + hpbar_width, hpbar_y + hpbar_height, Pallet::LemonYellow.GetHandle(), FALSE);

}
