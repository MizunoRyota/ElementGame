#include "stdafx.hpp"
#include "UiEnemyHpBar.hpp"
#include "Window.hpp"
#include "Enemy.hpp"
#include "DxLib.h"

// 敵 HP バー UI コンストラクタ
// 対象となる Enemy を weak_ptr で保持し寿命管理を委ねる
UiEnemyHpBar::UiEnemyHpBar(const std::shared_ptr<Enemy>& enemy)
    : enemy_(enemy)
{
    zOrder_ = 0; // 将来: 他 UI と重なり制御したい場合は外部から SetZ で変更
}

// 毎フレーム更新
// 実 HP(realHp) と表示用 HP(displayHp_) を分離し、減少のみ遅延表示で演出
void UiEnemyHpBar::Update(float dt)
{
    if (auto enemyLocked = enemy_.lock())
    {
        // 初回に最大 HP として現在値をキャッシュ（Enemy に明確な MaxHP API が無いため仮取得）
        if (maxHp_ == 0)
        {
            maxHp_ = enemyLocked->GetHp();
            displayHp_ = maxHp_;
        }

        int realHp = enemyLocked->GetHp();
        if (realHp < 0) realHp = 0;

        // ダメージ時: displayHp_ を catchUpSpeed_ 速度で追従減少
        if (displayHp_ > realHp)
        {
            int decayAmount = static_cast<int>(catchUpSpeed_ * dt);
            if (decayAmount < 1) decayAmount = 1; // 最低 1 減少
            displayHp_ -= decayAmount;
            if (displayHp_ < realHp) displayHp_ = realHp; // 行き過ぎ補正
        }
        // 回復時: 即時反映（必要なら遅延表現を追加可能）
        else if (displayHp_ < realHp)
        {
            displayHp_ = realHp;
            if (realHp > maxHp_) maxHp_ = realHp; // 予期せぬ最大値更新にも対応
        }
    }
}

// 描画処理
// 右上固定アンカー: 画面幅 - オフセット - バー幅 を基点 X に採用
void UiEnemyHpBar::Draw() const
{
    auto enemyLocked = enemy_.lock();
    if (!enemyLocked || maxHp_ <= 0) return; // 対象消滅 or 未初期化なら描画しない

    int realHp = enemyLocked->GetHp();
    if (realHp < 0) realHp = 0;

    float realRatio = static_cast<float>(realHp) / static_cast<float>(maxHp_);
    float delayedRatio = static_cast<float>(displayHp_) / static_cast<float>(maxHp_);
    // 0~1 にクランプ
    if (realRatio < 0) realRatio = 0; if (realRatio > 1) realRatio = 1;
    if (delayedRatio < 0) delayedRatio = 0; if (delayedRatio > 1) delayedRatio = 1;

    // 画面サイズ取得（失敗時フォールバック）
    int screenWidth, screenHeight;
    GetGraphSize(GetDrawScreen(), &screenWidth, &screenHeight); // 簡易取得
    if (screenWidth <= 0) screenWidth = 1920;
    if (screenHeight <= 0) screenHeight = 1080;

    int baseX = screenWidth - offsetX_ - width_; // 右端基準
    int baseY = offsetY_;

    // ---- 背景 / ベース ----
    DrawBox(baseX - 2, baseY - 2, baseX + width_ + 2, baseY + height_ + 2, GetColor(0, 0, 0), TRUE); // 外枠背景 (縁取り用)
    DrawBox(baseX, baseY, baseX + width_, baseY + height_, GetColor(64, 64, 64), TRUE);             // バー背景

    // ---- 遅延表示レイヤ（ダメージ演出: 暗赤）----
    int delayedWidth = static_cast<int>(width_ * delayedRatio);
    DrawBox(baseX, baseY, baseX + delayedWidth, baseY + height_, GetColor(150, 40, 40), TRUE);

    // ---- 実 HP レイヤ（上に重ねる）----
    int realWidth = static_cast<int>(width_ * realRatio);
    int colorR = 200; // 固定赤系ベース（好みに応じてグラデ調整可）
    int colorG = static_cast<int>(50 * realRatio);   // 減少で暗く
    int colorB = static_cast<int>(180 * realRatio);  // 減少で紫→赤寄り
    DrawBox(baseX, baseY, baseX + realWidth, baseY + height_, GetColor(colorR, colorG, colorB), TRUE);

    // ---- 枠線 ----
    DrawBox(baseX, baseY, baseX + width_, baseY + height_, GetColor(255, 255, 255), FALSE);

    // ---- テキスト（数値）----
    DrawFormatString(baseX, baseY + height_ + 8, GetColor(255, 255, 255), "ENEMY HP: %d / %d", realHp, maxHp_);
}