#pragma once
#include "../EnemyStateBase.hpp"
#include "EnemyAttackBase.hpp"

class EnemyStateBase;

// EnemyStateSpecialAttack:
// 特殊攻撃本体のステート。
/// - バリア（Barrior）をループ表示
/// - 指定フレームで Roar エフェクト再生＋特殊弾を発射
/// - アニメ終了で `STATE_CHOSEATTACK` へ戻る
class EnemyStateSpecialAttack : public EnemyStateBase, public EnemyAttackBase
{
public:
    EnemyStateSpecialAttack();
    ~EnemyStateSpecialAttack();

    void Enter() override;
    void Update() override;
    void Exit() override;

    EnemyStateKind GetNextState() override;

private:
    static constexpr float SPECIALBULLET_SPEED     = 0.3f; // 特殊弾（落下など）の速度
    static constexpr float SPECIALEATTACK_TIMING   = 35;   // 発射タイミング（アニメフレーム）

    // 未使用：チャージ時間等の拡張用
    float specialattack_charge_time;
};