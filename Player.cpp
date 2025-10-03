#include "stdafx.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "BulletFire.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "PlayerMove.hpp"
#include "PlayerAnimater.hpp"

Player::Player()
{
	obj_name = "Player"; // 名前識別

	// 3Dモデル読み込み
	obj_modelhandle = MV1LoadModel(_T("data/3dmodel/Player/Player.mv1"));
	
	character_handname  = MV1SearchFrame(obj_modelhandle, "f_middle.03.R"); // 右手末端フレームID
	// モデルスケール適用
	MV1SetScale(obj_modelhandle, VGet(SCALE, SCALE, SCALE));

	obj_position = VGet(0, 0, 0); // 初期位置
	obj_direction = VGet(0, 0, 0); // 向き(未使用初期化)

	player_animater = std::make_shared<PlayerAnimater>(obj_modelhandle,player_state); // アニメーション制御
	player_move = std::make_shared<PlayerMove>(); // 移動制御
	player_bullet = std::make_shared<BulletFire>(); // 弾発射

	player_state = STATE_HANDIDLE; // 初期ステート

	// 被弾後クール(30f)設定
	ConfigureDamageCooldown(30);
}

Player::~Player() {}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	obj_hp = PLAYER_MAXHP; // HP リセット
	obj_position = VGet(0, 0, 0);
	obj_direction = VGet(0, 0, 0);
	// モデル回転初期
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoceAngle() + DX_PI_F, 0.0f));
	// モデル座標適用
	MV1SetPosition(obj_modelhandle, obj_position);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{

	player_bullet->FireUpdate(); // 弾クール更新

	player_move->Update(input_reference, camera_reference); // 入力→移動量計算

	UpdateStateAction(); // 攻撃入力/ステート決定

	Move(); // 位置反映

	player_animater->Update(); // アニメーション更新

	// ★ 無敵タイマー減算
	TickDamageCooldown(); // 無敵タイマー
}

/// <summary>
/// 
/// </summary>
void Player::UpdateStateAction()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		player_state = STATE_ATTACK; // 攻撃ステート

		character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname); // 手先取得

		character_handposition = VAdd(character_handposition, VScale(camera_reference->GetCameraDir(), BULLETFIRE_DISTANCE)); // カメラ方向前方へオフセット

		player_bullet->FireStraight(character_handposition, camera_reference->GetCameraDir(), BULLET_SPEED); // 発射

	}
	else
	{
		player_state = STATE_HANDIDLE; // 待機
	}
}

/// <summary>
/// 
/// </summary>
void Player::Move()
{
	// 入力で得た移動量反映
	obj_position = VAdd(obj_position, player_move->GetMoveScale());

	CheckMoveRange(); // 範囲外補正
	// 当たり判定をして、新しい座標を保存する
	//position = stage.CheckCollision(*this, MoveVector);
	//プレイヤーの回転
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoceAngle() + DX_PI_F, 0.0f));
	//プレイヤーのモデルの設置
	MV1SetPosition(obj_modelhandle, obj_position);
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(obj_modelhandle); // 3D描画
}