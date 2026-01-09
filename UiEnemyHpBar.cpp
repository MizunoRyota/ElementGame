#include "stdafx.hpp"
#include "UiEnemyHpBar.hpp"
#include "Enemy.hpp"

// 敵 HP バー UI コンストラクタ
// 対象となる Enemy を weak_ptr で保持し寿命管理を委ねる
UiEnemyHpBar::UiEnemyHpBar(const std::shared_ptr<Enemy>& enemy)
    : enemy_(enemy)
{
    order_z = 0; // 背景層 (必要なら SetZ で変更)
}

// 毎フレーム更新
// 実 HP(hpbarReal) と表示用 HP(hpbar_display) を分離し、減少のみ遅延表示で演出
void UiEnemyHpBar::Update()
{
    if (auto enemy_locked = enemy_.lock())
    {
        if (hpbar_maxhp == 0) // 初回取得
        {
            hpbar_maxhp = enemy_locked->GetHp();
            hpbar_display = hpbar_maxhp;
        }
        int hpbarReal = enemy_locked->GetHp();
        if (hpbarReal < 0) hpbarReal = 0;

        // ダメージ時: hpbar_display を DELAY_SPEED 速度で追従減少
        if (hpbar_display > hpbarReal)
        {
            int decayAmount = static_cast<int>(DELAY_SPEED * DISPLAY_);
            if (decayAmount < 1) decayAmount = 1; // 最低 1 減少
            hpbar_display -= decayAmount;
            if (hpbar_display < hpbarReal) hpbar_display = hpbarReal; // 行き過ぎ補正
        }
        // 回復時: 即時反映（必要なら遅延表現を追加可能）
        else if (hpbar_display < hpbarReal)
        {
            hpbar_display = hpbarReal; // 回復は即時
            if (hpbarReal > hpbar_maxhp) hpbar_maxhp = hpbarReal; // 上限調整
        }
    }
}

// 描画処理
// 右上固定アンカー: 画面幅 - オフセット - バー幅 を基点 X に採用
void UiEnemyHpBar::Draw() const
{
    auto enemy_locked = enemy_.lock();
    if (!enemy_locked || hpbar_maxhp <= 0) return; // 対象消滅 or 未初期化なら描画しない

    int hpbarReal = enemy_locked->GetHp();
    if (hpbarReal < 0) hpbarReal = 0;

    float realRatio = static_cast<float>(hpbarReal) / static_cast<float>(hpbar_maxhp);
    float delayedRatio = static_cast<float>(hpbar_display) / static_cast<float>(hpbar_maxhp);
    // 0~1 にクランプ
    if (realRatio < 0) realRatio = 0; if (realRatio > 1) realRatio = 1;
    if (delayedRatio < 0) delayedRatio = 0; if (delayedRatio > 1) delayedRatio = 1;

    // 画面サイズ取得（失敗時フォールバック）
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;

    int hpbarX = SCREEN_WIDTH / 2 - 600; // 右上配置
    int hpbarY = offset_y;

    // ---- 背景 / ベース ----
    DrawBoxAA(hpbarX - BAR_FRAME, hpbarY - BAR_FRAME, hpbarX + hpbar_width + BAR_FRAME, hpbarY + hpbar_height + BAR_FRAME, Pallet::Aqua.GetHandle(), TRUE); // 外枠背景 (縁取り用)
    DrawBox(hpbarX, hpbarY, hpbarX + hpbar_width, hpbarY + hpbar_height, Pallet::Gray.GetHandle(), TRUE);             // バー背景

    // ---- 遅延表示レイヤ（ダメージ演出: 暗赤）----
    int hpbarDelayWidth = static_cast<int>(hpbar_width * delayedRatio);
    DrawBox(hpbarX, hpbarY, hpbarX + hpbarDelayWidth, hpbarY + hpbar_height,Pallet::Red.GetHandle(), TRUE);

    // ---- 実 HP レイヤ（上に重ねる）----
    int realWidth = static_cast<int>(hpbar_width * realRatio);
    int colorG = static_cast<int>(G_DECREASE_RAITO * realRatio);   // 減少で暗く
    int colorB = static_cast<int>(B_DECREASE_RAITO * realRatio);  // 減少で紫→赤寄り
    DrawBox(hpbarX, hpbarY, hpbarX + realWidth, hpbarY + hpbar_height, GetColor(BAR_R, colorG, colorB), TRUE);

    // ---- 枠線 ----
    DrawBox(hpbarX, hpbarY, hpbarX + hpbar_width, hpbarY + hpbar_height, Pallet::Aqua.GetHandle(), FALSE);

}