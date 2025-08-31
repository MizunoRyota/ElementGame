#include "stdafx.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "PlayerMove.hpp"
#include "PlayerAnimater.hpp"

Player::Player()
{

	obj_name = "Player";

	//3Dモデルハンドル
	obj_modelhandle = MV1LoadModel(_T("data/3dmodel/Player/Player.mv1"));
	
	// 3Dモデルのスケール決定
	MV1SetScale(obj_modelhandle, VGet(SCALE, SCALE, SCALE));

	obj_position = (VGet(0, 0, 0));
	obj_direction = VGet(0, 0, 0);

	player_animater = std::make_shared<PlayerAnimater>(obj_modelhandle,player_state);
	player_move = std::make_shared<PlayerMove>();

	player_state = STATE_HANDIDLE;

}

Player::~Player()
{
}

void Player::Initialize()
{
	obj_position = VGet(0, 0, 0);
	obj_direction = VGet(0, 0, 0);
	obj_hp = PLAYER_MAXHP;
}

void Player::Update()
{

	player_move->Update(input, camera);

	UpdateStateAction();

	Move();

	player_animater->Update();

}

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

void Player::UpdateStateAction()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		player_state = STATE_ATTACK;
	}
	else
	{
		player_state = STATE_HANDIDLE;
	}
}

void Player::Draw()
{
	MV1DrawModel(obj_modelhandle);
}