#pragma once
#include "CharacterBase.hpp"

class CharacterBase;
class GameObject;

// Crystal:
// `CharacterBase` を継承したギミックオブジェクト。
// - HP を持ち、弾などでダメージを受ける
// - 一定条件で破壊（ブレイク）状態へ遷移し、モデル/挙動が変化する
// - 通常のキャラクターのようなステート更新は持たない（必要な関数は空実装）
class Crystal : public CharacterBase
{
public:
    Crystal();
    ~Crystal();

    // json（モデル/当たり判定/初期値など）読み込み
    void LoadJson();

    // 初期化（モデル/HP/状態など）
    void Initialize() override;

    // 毎フレーム更新（回転/横移動など）
    void Update() override;

    // ステート更新は使わない
    void UpdateStateAction() override {};
    void UpdateHandEffect() override {};
    void InitializeStates() override {};

    // シーン別描画/更新（必要に応じてオーバーライドするが現状は空）
    void DrawTitle() override {};
    void Draw() override;
    void DrawGameOver() override {};
    void DrawGameClear() override {};

    void UpdateGameClear() override {};
    void UpdateGameOver() override {};
    void UpdateTitle() override {};
    void UpdateTutorial() override {};

    // アクティブ切替（出現/非表示などの制御）
    void ChangeActive();

    // 破壊（ブレイク）状態へ切り替え
    void ChangeBreak();

    // 横方向の移動（回転運動の補助など）
    void MoveHorizontal();

    // ブレイク状態を解除（リセット用）
    void ChangeCrystalIsBreak() { crystal_is_break = false; }

    // 初期化済み（アクティブ）か
    bool GetCrystalIsInit() const { return crystal_is_active; }

    // 破壊状態か
    bool GetCrystalIsBreak() const { return crystal_is_break; }

private:

    static constexpr float CRYSTAL_SCALE    = 0.010f; // モデルスケール
    static constexpr float ROTATION_RADIUS  = 7.0f;   // 回転半径
    static constexpr float ROTATION_SPEED   = 0.015f; // 回転角速度（rad/frame）
    static constexpr int   CRYSTAL_MAXHP    = 10;     // 最大HP
    static constexpr float OFFSET_Y         = 7.0f;   // 高さオフセット

    bool  crystal_is_active; // 使用中（出現済み）か
    bool  crystal_is_break;  // 破壊状態か
    float crystal_angle;     // 現在角度（回転用）

    json crystal_json_data;// json 設定データ
};
