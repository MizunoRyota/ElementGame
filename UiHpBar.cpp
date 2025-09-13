#include "stdafx.hpp"
#include "UiHpBar.hpp"
#include "Player.hpp"
#include "DxLib.h"

UiHpBar::UiHpBar(const std::shared_ptr<Player>& player)
    : player_(player)
{
    zOrder_ = 0; // HUD層

    // 初期数値をコンストラクタで設定
    if (auto playerLocked = player_.lock())
    {
        maxHp_ = playerLocked->GetHp();
        if (maxHp_ < 1) maxHp_ = 1; // 0除算防止
        displayHp_ = maxHp_;
    }
    else
    {
        maxHp_ = 1;       // 参照不可時の安全値
        displayHp_ = 1;
    }
}

void UiHpBar::Update(float dt)
{
    auto playerLocked = player_.lock();
    if (!playerLocked) return; // プレイヤー消滅等

    int realHp = playerLocked->GetHp();
    if (realHp < 0) realHp = 0;

    // Max HP を動的に上方更新（将来の最大値増加に対応）
    if (realHp > maxHp_) maxHp_ = realHp;

    if (displayHp_ > realHp)
    {
        // ダメージ時は遅延して追従
        int decayAmount = static_cast<int>(catchUpSpeed_ * dt);
        if (decayAmount < 1) decayAmount = 1;
        displayHp_ -= decayAmount;
        if (displayHp_ < realHp) displayHp_ = realHp; // 行き過ぎ補正
    }
    else if (displayHp_ < realHp)
    {
        // 回復は即座に反映（必要なら遅延処理追加可）
        displayHp_ = realHp;
    }
}

void UiHpBar::Draw() const
{
    auto playerLocked = player_.lock();
    if (!playerLocked || maxHp_ <= 0) return;

    int realHp = playerLocked->GetHp();
    if (realHp < 0) realHp = 0;

    float realRatio = static_cast<float>(realHp) / static_cast<float>(maxHp_);
    float delayedRatio = static_cast<float>(displayHp_) / static_cast<float>(maxHp_);
    if (realRatio < 0) realRatio = 0; if (realRatio > 1) realRatio = 1;
    if (delayedRatio < 0) delayedRatio = 0; if (delayedRatio > 1) delayedRatio = 1;

    // 背景
    DrawBox(baseX_ - 2, baseY_ - 2, baseX_ + width_ + 2, baseY_ + height_ + 2, GetColor(0, 0, 0), TRUE);
    DrawBox(baseX_, baseY_, baseX_ + width_, baseY_ + height_, GetColor(64, 64, 64), TRUE);

    // 遅延バー(赤寄り)
    int delayedWidth = static_cast<int>(width_ * delayedRatio);
    DrawBox(baseX_, baseY_, baseX_ + delayedWidth, baseY_ + height_, GetColor(180, 60, 60), TRUE);

    // 実HP(緑→黄→赤グラデ)
    int realWidth = static_cast<int>(width_ * realRatio);
    int colorR = static_cast<int>(255 * (1.0f - realRatio));
    int colorG = static_cast<int>(220 * realRatio);
    DrawBox(baseX_, baseY_, baseX_ + realWidth, baseY_ + height_, GetColor(colorR, colorG, 64), TRUE);

    // 枠
    DrawBox(baseX_, baseY_, baseX_ + width_, baseY_ + height_, GetColor(255, 255, 255), FALSE);

    // 数値
    SetFontSize(20);
    DrawFormatString(baseX_, baseY_ + height_ + 8, GetColor(255, 255, 255), "HP: %d / %d", realHp, maxHp_);
}
