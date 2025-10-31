#include "stdafx.hpp"
#include "Dodge.hpp"
#include "Enemy.hpp"

Dodge::Dodge()
{
    dodge_time = 0;
}

Dodge::~Dodge() {}

// 状態に応じて左右へステップ回避
VECTOR Dodge::DodgeEnemy(VECTOR& position, VECTOR& dir,EnemyState& state)
{
    if (dodge_time <= 0)
    {
        dodge_time = DODGE_TIMER;
    }
    else
    {
        dodge_time -= 0.5f;
    }
    // 方向ベクトルを正規化
    VECTOR forward = VNorm(dir);

    // Y軸基準の右方向ベクトル
    VECTOR up = VGet(0.0f, 1.0f, 0.0f);
    VECTOR right = VCross(up, forward);
    right = VNorm(right);

    float dodgeSpeed = DODGE_SPEED;

    if (state == STATE_RUNLEFT)
    {
        VECTOR newPos = VAdd(position, VScale(right, -dodgeSpeed));
        return newPos;
    }
    else if (state == STATE_RUNRIGHT)
    {
        VECTOR newPos = VAdd(position, VScale(right, dodgeSpeed));
        return newPos;
    }
    return position; // 想定外: 位置を維持
}

// 回避終了か
bool Dodge::GetIsDodgeEnd()
{
    return dodge_time <= 0;
}