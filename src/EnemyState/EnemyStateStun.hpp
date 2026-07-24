#pragma once

#include "../EnemyStateBase.hpp"

// EnemyStateStun:
// 敵が一定時間「スタン（行動不能）」になるステート。
// - Enter で残り時間をセットし、頭上にスタンエフェクトを出す
// - Update で時間を減らしつつ、エフェクト位置を敵に追従させる
// - 時間切れで `STATE_CHOSEATTACK` へ復帰
class EnemyStateStun : public EnemyStateBase
{
public:
    EnemyStateStun();
    ~EnemyStateStun();

    void Enter() override;
    void Update() override;
    void Exit() override;

    // 次ステート判定（時間切れ/被弾割り込みなど）
    EnemyStateKind GetNextState() override;

private:
    // スタン継続時間（フレーム/疑似時間として扱う）
    static constexpr float STUN_TIME = 2000.0f;

    // スタンエフェクトの表示高さ（敵座標からのYオフセット）
    static constexpr float STUN_HEIGHT = 2.5f;

    // 1更新あたりのスタン時間減算量
    static constexpr float STUN_DECREASE_TIME = 10.0f;

    // 残りスタン時間
    float stun_time;
};