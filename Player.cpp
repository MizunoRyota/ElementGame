#include "stdafx.hpp"
#include "Player.hpp"
#include "PlayerStateBase.hpp"
#include "PlayerAttack.hpp"
#include "BulletFire.hpp"
#include "PlayerMove.hpp"
#include "PlayerAnimater.hpp"
#include "src/PlayerState/PlayerStateIdle.hpp";
#include "src/PlayerState/PlayerLaserState.hpp"
#include "ObjectAccessor.hpp"

// プレイヤー生成と初期セットアップ
Player::Player()
{
	COLLISION_CAPSULE_RADIUS = 0.06f; // カプセル判定半径
	COLLISION_CAPSULE_HEIGHT = 2.5f;  // カプセル判定高さ

	obj_name = "Player"; // 名前識別
	// 3Dモデル読み込み
	obj_modelhandle = MV1LoadModel(_T("data/3dmodel/Player/Player.mv1"));
	character_hand_position = MV1GetFramePosition(obj_modelhandle, character_handname); // 手先取得
	character_handname = MV1SearchFrame(obj_modelhandle, "f_middle.03.R"); // 右手末端フレームID

	// モデルスケール適用
	MV1SetScale(obj_modelhandle, VGet(SCALE, SCALE, SCALE));

	// 状態テーブル初期化（重要）
	InitializeStates();

	player_state_kind = PlayerStateKind::STATE_IDLE;

	// 初期ステートは具体クラスを生成（抽象クラスは生成不可）
	player_current_state = std::make_shared<PlayerAttack>();

	player_animater = std::make_shared<PlayerAnimater>(obj_modelhandle, player_state_kind); // アニメーション制御
	player_move = std::make_shared<PlayerMove>();   // 移動制御

	// 被弾後クール(5f)設定
	ConfigureDamageCooldown(TAKEDAMAGE_COOLDOWN);
}

Player::~Player() 
{
	MV1DeleteModel(obj_modelhandle);
}

// 初期化（位置/向き/モデル姿勢などを初期状態に）
void Player::Initialize()
{
	obj_hp = PLAYER_MAXHP; // HP リセット
	obj_position = VGet(0, 0, 0);
	obj_direction = VGet(0, 0, 1);
	// モデル回転初期
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoveAngle() + DX_PI_F, 0.0f));
	// モデル座標適用
	MV1SetPosition(obj_modelhandle, obj_position);

}

void Player::InitializeStates()
{
    states[PlayerStateKind::STATE_IDLE]   = std::make_shared<PlayerStateIdle>();   // STATE_IDLE用の具体クラスに差し替え
    states[PlayerStateKind::STATE_ATTACK] = std::make_shared<PlayerAttack>();
	states[PlayerStateKind::STATE_LASER] = std::make_shared<PlayerLaserState>();
}

// 毎フレーム更新
void Player::Update()
{

	// デバッグ: Kキーで強制死亡
	if ((CheckHitKey(KEY_INPUT_K) != 0))
	{
		obj_hp = 0;
	}

	player_move->Update(); // 入力→移動量計算

	Move(); // 位置反映

	UpdateStateAction(); // 攻撃入力/ステート決定

	UpdateHandEffect(); // 手元エフェクト位置更新

	player_animater->Update(); // アニメーション更新

	// 無敵タイマー減算
	TickDamageCooldown();
}

// 手元ループエフェクトの位置更新
void Player::UpdateHandEffect()
{
	// 手元ループエフェクト
	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::HandEffect, character_hand_position);
	//ポジションをセット
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::HandEffect, character_hand_position);
}

// 攻撃入力に応じてステートを切替え、弾を発射
void Player::UpdateStateAction()
{

	player_state_kind = player_current_state->GetNextState();

	if (player_current_state != states.at(player_state_kind))
	{
		player_current_state->Exit();
		player_current_state = states.at(player_state_kind);
		player_current_state->Enter();
	}

	player_current_state->Update();

}

// 入力で得た移動量を反映し、モデル姿勢/位置を適用
void Player::Move()
{
	// 入力で得た移動量反映
	obj_position = VAdd(obj_position, player_move->GetMoveScale());

	CheckMoveRange(); // 範囲外補正

	// プレイヤーの回転
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoveAngle() + DX_PI_F, 0.0f));
	// プレイヤーモデルの配置
	MV1SetPosition(obj_modelhandle, obj_position);

	character_hand_position = MV1GetFramePosition(obj_modelhandle, character_handname); // 手先取得

}

VECTOR Player::GetLaserEndPosition()
{
	return (VAdd(character_hand_position, VScale(ObjectAccessor::GetObjectAccessor().GetCameraDirection(), LASER_MAX_LENGTH)));
}

// 描画
void Player::Draw()
{
	MV1DrawModel(obj_modelhandle); // 3D描画

	clsDx();

	if (ChengeDebugFlag())
	{
		SetLogDrawArea(0, 100, 600, 1000);
		setPrintColorDx(Pallet::LemonYellow.GetHandle());
		printfDx("PlayerState %s\n", PlayerStateToString(player_state_kind));
		printfDx("PlayerPosition.x: %f", obj_position.x);
		printfDx(" y %f", obj_position.y);
		printfDx(" z %f\n\n",obj_position.z);
		DrawCapsule3D(obj_position, VAdd(obj_position, VGet(0, COLLISION_CAPSULE_HEIGHT, 0)), COLLISION_CAPSULE_RADIUS, 16, Pallet::Red.GetHandle(), Pallet::Red.GetHandle(), false);

	}
}