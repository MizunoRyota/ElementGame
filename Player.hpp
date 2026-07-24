#pragma once
#include "CharacterBase.hpp"
#include "PlayerStateKind.hpp"

class GameObject;
class IState;
class CharaterBase;
class AnimaterBase;
class PlayerStateBase;
class PlayerMove;
class PlayerJump;
class Laser;
class BulletFire;

// Player:
// `CharacterBase` を継承した操作キャラクター。
//// - `PlayerMove`/`PlayerJump` で移動・ジャンプの計算を行う
//// - ステート（`PlayerStateBase` 派生）で攻撃/レーザーなどの行動を切り替える
//// - アニメータ（`AnimaterBase`）に状態を伝えて見た目を更新する
class Player : public CharacterBase
{
public:
    Player();
    ~Player() override;

    // 初期化（HP/位置/状態/モデル設定など）
    void Initialize() override;

    // json（モデル/手元フレーム/当たり判定など）読み込み
    void LoadJson();

    // ステート一覧を生成して `states` に登録
    void InitializeStates() override;

    // 手元追従エフェクトなどの更新
    void UpdateHandEffect() override;

    // 毎フレーム更新
    void Update() override;

    // 入力に応じた移動反映（モデルの位置/向きへの反映も含む）
    void Move();

    // 描画
    void Draw() override;

    void DrawGameClear()override {};
    void DrawGameOver() override {};
    // ステートの遷移・更新
    void UpdateStateAction() override;

    // シーン別更新（未使用のものは空実装）
    void UpdateGameClear() override {};
    void UpdateGameOver() override {};
    void UpdateTitle() override {};
    void UpdateTutorial() override;

    // 衝突解決用の押し戻し（ノックバック）適用
    void ApplyKnockback(const VECTOR& knockback);

    // サブコンポーネント/状態取得
    std::shared_ptr<PlayerMove> GetPlayerMove() const { return player_move; }

    PlayerStateKind GetPlayerStateKind() const { return player_state_kind; }

    // レーザーの終端位置（手元位置 + カメラ前方 * 最大長）
    VECTOR GetLaserEndPosition();

	void ChangeIsReadyLaser(bool is_ready) { laser_is_ready = is_ready; }

	bool GetIsReadyLaser() { return laser_is_ready; }
    
private:
    // ===== 調整用定数 =====
    static constexpr float SCALE            = 0.01f;  // モデルスケール
    static constexpr int   PLAYER_MAXHP     = 150;    // 最大HP
    static constexpr float LASER_MAX_LENGTH = 30.0f;  // レーザー最大射程

    // ===== サブコンポーネント =====
    std::shared_ptr<AnimaterBase> player_animater; // アニメ制御
    std::shared_ptr<PlayerMove>   player_move;     // 移動入力/移動量計算
    std::shared_ptr<PlayerJump>   player_jump;     // ジャンプの物理/状態

    // ===== ステートマシン =====
    std::shared_ptr<PlayerStateBase> player_current_state;
    std::unordered_map<PlayerStateKind, std::shared_ptr<PlayerStateBase>> states;

    // 現在のプレイヤーステート種別
    PlayerStateKind player_state_kind;

    // json 設定データ
    json player_json_data;

	//レーザーが撃てるかのフラグ
    bool laser_is_ready;

};