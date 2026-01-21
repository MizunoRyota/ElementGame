#pragma once
#include <unordered_map>
#include "EnemyStateKind.hpp"
#include "AnimaterBase.hpp"

// 敵用のアニメーション制御クラス。
// EnemyStateKind を参照して、適切なアニメーションへ切り替える。
class EnemyAnimater : public AnimaterBase
{
public:
    // コンストラクタ
    // modelhandle: モデルハンドル, enemystate: 敵の状態(参照保持)
    EnemyAnimater(int modelhandle,  EnemyStateKind& enemystate);
    virtual ~EnemyAnimater();

    void InitializeAnimationData() override; // アニメーションデータ登録
    void Update() override;                  // 毎フレーム更新
    void SwitchAnimation() override;         // 状態に応じてアニメ切替

protected:
    EnemyStateKind& enemy_state; // 参照保持：敵の現在ステート

private:
    static constexpr float DEFAULT_ANIMATION_SPEED = 0.5f;
    static constexpr float SPECIALATTACK_ANIMATION_SPEED = 0.25f;

};