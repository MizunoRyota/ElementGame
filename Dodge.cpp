#include "stdafx.hpp"
#include "Dodge.hpp"
#include "Enemy.hpp"

Dodge::Dodge()
    :dodge_time(0)
{
}

Dodge::~Dodge()
{
}

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
    // 正規化（方向ベクトルを長さ1にする）
    VECTOR forward = VNorm(dir);

    // Y軸を基準にして横方向を計算（クロス積）
    VECTOR up = VGet(0.0f, 1.0f, 0.0f);
    VECTOR right = VCross(up, forward);

    right = VNorm(right);

    // 横移動のスピード
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
}

bool Dodge::GetIsDodgeEnd()
{
    return dodge_time <= 0;
}