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

	obj_name = "Player";

	//3Dモデルハンドル
	obj_modelhandle = MV1LoadModel(_T("data/3dmodel/Player/Player.mv1"));
	
	character_handname  = MV1SearchFrame(obj_modelhandle, "f_middle.03.R");
	// 3Dモデルのスケール決定
	MV1SetScale(obj_modelhandle, VGet(SCALE, SCALE, SCALE));

	obj_position = (VGet(0, 0, 0));
	obj_direction = VGet(0, 0, 0);

	player_animater = std::make_shared<PlayerAnimater>(obj_modelhandle,player_state);
	player_move = std::make_shared<PlayerMove>();

	player_bullet = std::make_shared<BulletFire>();

	player_state = STATE_HANDIDLE;

	// ★ プレイヤーのダメージ無敵フレーム（例: 30f）
	ConfigureDamageCooldown(30);
}

Player::~Player()
{
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	obj_hp = PLAYER_MAXHP;
	obj_position = VGet(0, 0, 0);
	obj_direction = VGet(0, 0, 0);
	//プレイヤーの回転
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoceAngle() + DX_PI_F, 0.0f));
	//プレイヤーのモデルの設置
	MV1SetPosition(obj_modelhandle, obj_position);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{

	player_bullet->FireUpdate();

	player_move->Update(input_reference, camera_reference);

	UpdateStateAction();

	Move();

	player_animater->Update();

	// ★ 無敵タイマー減算
	TickDamageCooldown();
}


/// <summary>
/// 
/// </summary>
void Player::UpdateStateAction()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		player_state = STATE_ATTACK;

		character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname);

		player_bullet->FireHoming(character_handposition, camera_reference->GetCameraDir(), BULLET_SPEED, enemy_reference);

	}
	else
	{
		player_state = STATE_HANDIDLE;
	}
}

/// <summary>
/// 
/// </summary>
void Player::Move()
{
	//プレイヤーの座標変更
	obj_position = VAdd(obj_position, player_move->GetMoveScale());
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
	MV1DrawModel(obj_modelhandle);
}