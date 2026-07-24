#include "stdafx.hpp"
#include "Player.hpp"
#include "PlayerStateBase.hpp"
#include "PlayerAttack.hpp"
#include "PlayerMove.hpp"
#include "PlayerJump.hpp"
#include "PlayerAnimater.hpp"
#include "EffectCreator.hpp"
#include "src/PlayerState/PlayerStateIdle.hpp"
#include "src/PlayerState/PlayerStateLaser.hpp"
#include "ObjectAccessor.hpp"

// Player:
// - 入力（`PlayerMove`）とジャンプ（`PlayerJump`）で位置を決定
// - ステート（`PlayerStateBase` 派生）で攻撃などの行動を切り替え
// - アニメータ（`PlayerAnimater`）で見た目を状態に同期
// - 手元エフェクトなどの演出もここで位置更新する
Player::Player()
{
    // GameObject 識別用の名前タグ（SharedData::FindObject などで使用）
    obj_name = "Player";

	laser_is_ready = false;

    // プレイヤー設定は json から読み込む（モデルパス/カプセルサイズなど）
    std::ifstream file{ "Player.json" };
    player_json_data = json::parse(file);

    LoadJson();

    // 各ステートの登録（重要：状態遷移の行き先をここで用意する）
    InitializeStates();

    // 初期状態は待機
    player_state_kind = PlayerStateKind::STATE_IDLE;
    player_current_state = std::make_shared<PlayerStateIdle>();

    // 見た目・移動・ジャンプなどのサブコンポーネント
    player_animater = std::make_shared<PlayerAnimater>(obj_modelhandle, player_state_kind);
    player_move = std::make_shared<PlayerMove>();
    player_jump = std::make_shared<PlayerJump>(obj_position);

    // 被弾クールタイム（連続ヒット抑制）
    ConfigureDamageCooldown(TAKEDAMAGE_COOLDOWN);
}

Player::~Player()
{
    // モデルは Player が所有し破棄する
    MV1DeleteModel(obj_modelhandle);
}
/// <summary>
/// Jsonの読み込み
/// </summary>
void Player::LoadJson()
{
    // 3Dモデル/手元フレーム名/当たり判定カプセルを json から取得
    std::string modelPath = player_json_data["player_model"];
    std::string handnamePath = player_json_data["player_hand_name"];
    float cuapsuleHeight = player_json_data["player_capsule_height"];
    float cuapsuleRadius = player_json_data["player_capsule_radius"];

    // 当たり判定（カプセル）のサイズ
    COLLISION_CAPSULE_HEIGHT = cuapsuleHeight;
    COLLISION_CAPSULE_RADIUS = cuapsuleRadius;

    // モデル読み込みと手元（武器/レーザー発射位置）フレームの取得
    obj_modelhandle = MV1LoadModel(modelPath.c_str());
    character_handname = MV1SearchFrame(obj_modelhandle, handnamePath.c_str());
    character_hand_position = MV1GetFramePosition(obj_modelhandle, character_handname);

    // モデルスケール適用
    MV1SetScale(obj_modelhandle, VGet(SCALE, SCALE, SCALE));
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
    // プレイヤーの初期化（開始地点/向き/HP/状態など）
    obj_hp = PLAYER_MAXHP;
    obj_position = VGet(0, 0, 0);
    obj_direction = VGet(0, 0, 1);
    laser_is_ready = false;
    // プレイヤーの移動コンポーネントを初期化
    player_move->Initialize();

    // ステートを待機へリセット
    player_current_state->Exit();
    player_state_kind = PlayerStateKind::STATE_IDLE;
    player_current_state = std::make_shared<PlayerStateIdle>();

    // モデルへ向き・位置を反映
    MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoveAngle() + DX_PI_F, 0.0f));
    MV1SetPosition(obj_modelhandle, obj_position);
}

/// <summary>
/// ステートの初期化
/// </summary>
void Player::InitializeStates()
{
    // ステート種別と実体の対応表
    // ※ states.at(kind) で取り出すため、使用する種別は必ず登録しておく
    states[PlayerStateKind::STATE_IDLE] = std::make_shared<PlayerStateIdle>();
    states[PlayerStateKind::STATE_ATTACK] = std::make_shared<PlayerAttack>();
    states[PlayerStateKind::STATE_LASER] = std::make_shared<PlayerStateLaser>();
}

/// <summary>
/// 初期化
/// </summary>
void Player::Update()
{
    // 入力から移動量や旋回角を更新
    player_move->Update();

    // ジャンプ（Y方向など）更新
    player_jump->Update();

    // 位置反映（範囲制限・モデルへの反映も含む）
    Move();

    // ステート遷移/攻撃処理など
    UpdateStateAction();

    // 手元の位置に追従するループエフェクト更新
    UpdateHandEffect();

    // アニメーション更新
    player_animater->Update();

    // 被弾クールタイム進行
    TickDamageCooldown();

}

/// <summary>
/// チュートリアル更新
/// </summary>
void Player::UpdateTutorial()
{
    // チュートリアルでは状態遷移を抑制して待機に固定する想定
    player_state_kind = PlayerStateKind::STATE_IDLE;
    player_animater->Update();
}

/// <summary>
/// プレイヤーのノックバック
/// </summary>
/// <param name="knockback">適用するノックバックベクトル。プレイヤーの位置に加算されます。</param>
void Player::ApplyKnockback(const VECTOR& knockback)
{
    // 衝突解決用の押し戻し（位置のみを加算）
    obj_position = VAdd(obj_position, knockback);

    // モデルに即時反映（押し戻しは瞬間的に適用する）
    MV1SetPosition(obj_modelhandle, obj_position);
    MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoveAngle() + DX_PI_F, 0.0f));

    // 手元位置も更新して、射撃/エフェクトがズレないようにする
    character_hand_position = MV1GetFramePosition(obj_modelhandle, character_handname);
}

/// <summary>
/// プレイヤーの手元エフェクトを更新
/// </summary>
void Player::UpdateHandEffect()
{
    // 手元に常時追従するループエフェクト
    // PlayLoop は未再生なら開始、再生中なら継続させる想定
    EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::HandEffect, character_hand_position);

    // 毎フレーム位置を更新して追従させる
    EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::HandEffect, character_hand_position);

}

/// <summary>
/// ステートの更新
/// </summary>
void Player::UpdateStateAction()
{

    // 現在ステートが次に遷移したいステートを問い合わせる
    player_state_kind = player_current_state->GetNextState();

    // 遷移が必要なら Exit→Enter を実行
    if (player_current_state != states.at(player_state_kind))
    {
        player_current_state->Exit();
        player_current_state = states.at(player_state_kind);
        player_current_state->Enter();
    }

    // 現在ステートの更新（攻撃発射などの主処理）
    player_current_state->Update();

}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move()
{
    // 入力により決定された移動量を反映
    obj_position = VAdd(obj_position, player_move->GetMoveScale());

    // ステージ外に出ないようクランプなどを行う
    CheckMoveRange();

    // モデルの向き（移動入力角度）
    MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoveAngle() + DX_PI_F, 0.0f));
    // モデルの位置
    MV1SetPosition(obj_modelhandle, obj_position);

    // 手元フレーム位置を更新（レーザー始点/エフェクト追従に使用）
    character_hand_position = MV1GetFramePosition(obj_modelhandle, character_handname); // 手先取得

}

/// <summary>
/// レーザーの終端位置を取得
/// </summary>
/// <returns>手元位置からカメラの前方方向へレーザーの最大長分伸ばした位置ベクトル。</returns>
VECTOR Player::GetLaserEndPosition()
{
    // レーザー終端：手元位置からカメラの前方方向へ最大長分伸ばした点
    return VAdd(character_hand_position,
        VScale(ObjectAccessor::GetObjectAccessor().GetCameraDirection(), LASER_MAX_LENGTH));
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
    // 3Dモデル描画
    MV1DrawModel(obj_modelhandle); // 3D描画

#ifndef NDEBUG

    // デバッグ表示
    clsDx();

    if (ChengeDebugFlag())
    {
        SetLogDrawArea(0, 100, 600, 1000);
        setPrintColorDx(Pallet::Red.GetHandle());
        printfDx("PlayerState %s\n", PlayerStateToString(player_state_kind));
        setPrintColorDx(Pallet::White.GetHandle());

        printfDx("PlayerPosition.x: %f", obj_position.x);
        printfDx(" y %f", obj_position.y);
        printfDx(" z %f\n\n", obj_position.z);

        // 当たり判定カプセルの可視化
        DrawCapsule3D(
            obj_position,
            VAdd(obj_position, VGet(0, COLLISION_CAPSULE_HEIGHT, 0)),
            COLLISION_CAPSULE_RADIUS,
            16,
            Pallet::Red.GetHandle(), Pallet::Red.GetHandle(),
            false);

    }

#endif
}

