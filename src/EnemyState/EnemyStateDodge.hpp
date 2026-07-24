#pragma once
#include "../EnemyStateBase.hpp"

// EnemyStateDodge:
// 左右への回避移動（RUNLEFT/RUNRIGHT）を行うステート。
// - 敵の前方向から右ベクトルを求め、左右にストレイフ移動する
// - 一定時間経過で `STATE_CHASE` へ遷移
// - 追尾/攻撃の事前準備として手元エフェクトを出す
class EnemyStateDodge : public EnemyStateBase
{
public:
    EnemyStateDodge(VECTOR& position);
    ~EnemyStateDodge();

    void Enter() override;
    void Update() override;
    void Exit() override;

    EnemyStateKind GetNextState() override;

private:
    static constexpr float DODGE_TIMER = 60.0f;                 // 回避継続フレーム（疑似時間）
    static constexpr float DODGE_SPEED = 0.2f;                  // 回避移動速度
    static constexpr float DODGE_DECREACE_TIME_SPEED = 0.5f;    // 1更新あたりのタイマー減算量

    float dodge_time;       // 残り回避時間
    VECTOR& dodge_position; // 敵位置参照
};
