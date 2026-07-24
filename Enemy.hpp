#pragma once
#include "CharacterBase.hpp"
#include "EnemyStateKind.hpp"
#include "AnimaterBase.hpp"

class GameObject;
class CharaterBase;
class EnemyStateBase;
class AnimaterBase;
class EnemyAnimater;
class Player;
class BulletFire;
class EnemyMove;
class SpecialAttack;

// Enemy:
// `CharacterBase` を継承した敵キャラクター。
// - ステートマシン（`EnemyStateBase` 派生）で行動を切り替える
// - アニメータ（`AnimaterBase`）で状態に応じたアニメ再生を行う
// - `EnemyMove` により追従/回転などの移動ロジックを委譲する
class Enemy : public CharacterBase
{
public:
    Enemy();
    ~Enemy() override;

    // json（モデル/当たり判定/初期値など）読み込み
    void LoadJson();

    // 初期化（HP/位置/状態/モデル設定など）
    void Initialize() override;

    // ステート一覧を生成して `states` に登録
    void InitializeStates() override;

    // ゲーム開始時の初期ステートを設定
    void InitializeGame() { enemy_state_kind = EnemyStateKind::STATE_CHARGE; }

    // 毎フレーム更新
    void Update() override;

    // シーン別更新（必要に応じて演出/入力制限などを行う想定）
    void UpdateGameClear() override;
    void UpdateGameOver() override;
    void UpdateTitle() override;
    void UpdateTutorial() override;

    // ステート遷移・各ステート更新の実行
    void UpdateStateAction() override;

    // 敵は手元エフェクト更新を使わない想定（必要なら実装）
    void UpdateHandEffect() override {};

    // プレイヤー方向へ向く等の角度更新
    void UpdateAngle();

    // スポーン地点などへ強制的に位置を設定
    void SetPosition();

    // 描画
    void Draw() override;
    void DrawGameOver() override { Draw(); };
    void DrawGameClear() override { Draw(); };
    // ===== 状態/情報取得 =====

    // 敵の向き（弾の発射方向やエフェクト向きに使用）
    const VECTOR& GetEnemyDirection() const { return obj_direction; }

    // 現在の敵ステート
    const EnemyStateKind& GetEnemyStateKind() const { return enemy_state_kind; }

    // 敵の与ダメージ基礎値（近接攻撃などで使用）
    const int& GetDamageStrength() const { return DAMAGE_STRENGTH; }

    // アニメ終了フラグ（ステート側の遷移条件に使用）
    bool GetAnimationIsEnd() const { return enemy_animater->GetAmimIsEnd(); }

    // 現在のアニメフレーム（遷移/当たり判定発生フレームなどに利用）
    float GetAnimationFrame() const { return enemy_animater->GetAnimationFrame(); }

    // 被弾エフェクトの発生位置（胴体付近の高さへオフセット）
    VECTOR GetHitPosition() const { return VAdd(obj_position, VGet(0, ENEMY_HITEFFECT_HEIGHT, 0)); }

    // 手元エフェクト停止（攻撃ステート切り替え時などの後処理用）
    void StopEnemyHandEffect();

    // 最大HP（UI表示などで使用）
    int GetEnemyMaxHp() const { return ENEMY_MAXHP; }

private:
    // ===== 調整用定数（ダメージ/スケール/初期位置など） =====
    static constexpr int   DAMAGE_STRENGTH          = 10;   // 与ダメージ基礎値
    static constexpr float ENEMY_HITEFFECT_HEIGHT   = 2.5f; // 被弾エフェクトの高さ
    static constexpr float ENEMY_SCALE              = 0.02f;// モデルスケール
    static constexpr int   ENEMY_MAXHP              = 150;  // 最大HP
    static constexpr float ENEMY_INIT_POSITION      = 20.0f;// 初期配置（距離）

    // ===== 状態フラグ =====
    bool enemy_is_die; // 死亡状態か

    // ===== エフェクト管理 =====
    // 手元エフェクトのハンドル（-1 は未再生）
    int enemy_hand_effect_handle = -1;

    // どの攻撃ステートで生成したエフェクトか（ステート跨ぎの停止判定に利用）
    int enemy_hand_effect_attack_state = -1;

    // ===== サブコンポーネント =====
    std::shared_ptr<AnimaterBase> enemy_animater; // アニメ制御
    std::shared_ptr<EnemyMove>    enemy_move;     // 移動/追従/回転など

    // ===== ステートマシン =====
    std::shared_ptr<EnemyStateBase> enemy_current_state;
    std::unordered_map<EnemyStateKind, std::shared_ptr<EnemyStateBase>> states;

    // 現在の敵ステート種別
    EnemyStateKind enemy_state_kind;

    // json 設定データ
    json enemy_json_data;
};