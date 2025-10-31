#pragma once
#include <unordered_map>
#include "EnemyState.hpp"
#include "AnimaterBase.hpp"

// 敵用のアニメーション制御クラス。
// EnemyState を参照して、適切なアニメーションへ切り替える。
class EnemyAnimater : public AnimaterBase
{
public:
    // コンストラクタ
    // modelhandle: モデルハンドル, enemystate: 敵の状態(参照保持)
    EnemyAnimater(int modelhandle,  EnemyState& enemystate);
    virtual ~EnemyAnimater();

    // 敵のアニメーション種別
    enum class AnimKind : int
    {
        Plalsy = 0,        // 痺れ（Palsy）
        WalkBack = 1,      // 後退
        Die = 2,           // 倒れる
        SpecialCharge = 3, // 特殊攻撃溜め
        Float = 4,         // 浮遊
        SpecialAttack = 5, // 特殊攻撃
        RunLeft = 6,       // 左へ走る
        Charge = 7,        // 突進
        RunRight = 8,      // 右へ走る
        FireAttack = 9,    // 火攻撃
        WaterAttack = 10,  // 水攻撃
        WindAttack = 11,   // 風攻撃
        JumpAttack = 12,   // ジャンプ攻撃
        Idle = 13,         // 待機
        Chase = 14,        // 追跡
        OnDamage = 15,     // 被ダメージ
    };

    void InitializeAnimationData() override; // アニメーションデータ登録
    void Update() override;                  // 毎フレーム更新
    void SwitchAnimation() override;         // 状態に応じてアニメ切替

protected:
    EnemyState& enemy_state; // 参照保持：敵の現在ステート
};