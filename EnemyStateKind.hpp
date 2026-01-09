#pragma once
//アニメーションを変更するときはanimation_dataの中身を変更することをわすれないで！！！
enum class EnemyStateKind : int
{
    STATE_STUN = 0,        // 痺れ（Stun）
    STATE_WALKBACK = 1,      // 後退
    STATE_DIE = 2,           // 倒れる
    STATE_SPECIAL_CHARGE = 3, // 特殊攻撃溜め
    STATE_FLOAT = 4,         // 浮遊
    STATE_SPECIALATTACK = 5, // 特殊攻撃
    STATE_RUNLEFT = 6,       // 左へ走る
    STATE_CHARGE = 7,        // 突進
    STATE_RUNRIGHT = 8,      // 右へ走る
    STATE_FIREATTACK = 9,    // 火攻撃
    STATE_WATERATTACK = 10,  // 水攻撃
    STATE_WINDATTACK = 11,   // 風攻撃
    STATE_JUMPATTACK = 12,   // ジャンプ攻撃
    STATE_IDLE = 13,         // 待機
    STATE_CHASE = 14,        // 追跡
    STATE_ONDAMAGE = 15,     // 被ダメージ
};

inline const char* EnemyStateToString(EnemyStateKind state) {
    switch (state) {
    case EnemyStateKind::STATE_IDLE: return "IDLE";
    case EnemyStateKind::STATE_CHARGE: return "CHARGE";
    case EnemyStateKind::STATE_RUNLEFT: return "RUNLEFT";
    case EnemyStateKind::STATE_RUNRIGHT: return "RUNRIGHT";
    case EnemyStateKind::STATE_CHASE: return "CHASE";
    case EnemyStateKind::STATE_FIREATTACK: return "FIREATTACK";
    case EnemyStateKind::STATE_WATERATTACK: return "WATERATTACK";
    case EnemyStateKind::STATE_WINDATTACK: return "WINDATTACK";
    case EnemyStateKind::STATE_WALKBACK: return "WALKBACK";
    case EnemyStateKind::STATE_FLOAT: return "FLOAT";
    case EnemyStateKind::STATE_SPECIAL_CHARGE: return "SPECIAL_CHARGE";
    case EnemyStateKind::STATE_SPECIALATTACK: return "SPECIALATTACK";
    case EnemyStateKind::STATE_ONDAMAGE: return "ONDAMAGE";
    case EnemyStateKind::STATE_DIE: return "DIE";
    case EnemyStateKind::STATE_STUN: return "Stun";
    default: return "UNKNOWN";
    }
}