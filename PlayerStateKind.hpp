#pragma once
// プレイヤーステート
enum class PlayerStateKind : int
{
    STATE_IDLE   = 9,  // 待機
    STATE_ATTACK = 7,  // 攻撃
    STATE_LASER = 8,  // 攻撃
};

inline const char* PlayerStateToString(PlayerStateKind state) {
    switch (state) {
    case PlayerStateKind::STATE_IDLE: return "IDLE";
    case PlayerStateKind::STATE_ATTACK: return "ATTACK";
    case PlayerStateKind::STATE_LASER: return "LASER";
    default: return "UNKNOWN";
    }
}