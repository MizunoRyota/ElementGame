#include<iostream>
#include"DxLib.h"
#include "Camera.hpp"
#include "Input.hpp"
#include"PlayerBase.hpp"
#include "BulletManager.hpp"
PlayerBase::PlayerBase()
	:position(VGet(0.0f, 0.0f,0.0f))
	,hand_name(0)
{
	model_handle = MV1LoadModel(_T("data/3dmodel/Player/Player.mv1"));
	hand_name = MV1SearchFrame(model_handle, "f_middle.03.R");
	// 3Dモデルのスケール決定
	MV1SetScale(model_handle, VGet(Scale, Scale, Scale));
	MV1SetPosition(model_handle, position);
	player_move = std::make_shared<PlayerMove>();
	attack_manager = std::make_shared<PlayerAttackManager>(model_handle);

}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Initialize() 
{

}
void PlayerBase::Update(const Input& input, const Camera& camera)
{
	clsDx();
	printfDx("playerxpos%f\n", position.x);
	printfDx("playerzpos%f\n", position.z);
	hand_position = MV1GetFramePosition(model_handle, hand_name);

	player_move->Update(input, camera);
	Move(player_move->GetMoveScale());
	FireBullet(input, camera);
	//attack_manager->Update(input, camera);
	LimitRange();
}

void PlayerBase::FireBullet(const Input& input, const Camera& camera)
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		bullet_manager->Shot(hand_position, camera.GetCameraDir());
	}
}

void PlayerBase::Move(const VECTOR& MoveVector)
{
	//プレイヤーの座標変更
	position = VAdd(position, player_move->GetMoveScale());
	// 当たり判定をして、新しい座標を保存する
	//position = stage.CheckCollision(*this, MoveVector);
	//プレイヤーの回転
	MV1SetRotationXYZ(model_handle, VGet(0.0f, player_move->GetMoceAngle() + DX_PI_F, 0.0f));
	//プレイヤーのモデルの設置
	MV1SetPosition(model_handle, position);
}

void PlayerBase::LimitRange()
{
	////中心からプレイヤーの距離を測る
	float r = VSize(VSub(position, VGet(0.0f, 0.0f, 0.0f)));

	////一定の距離に達したらそれ以上いけないようにする

	if (r > ReturnRange || r < -ReturnRange)
	{
		printfDx("returnRange%f\n", r);

		//中心座標からプレイヤー座標の距離

		VECTOR distance = VSub(VGet(0.0f, 0.0f, 0.0f), position);

		//正規化

		distance = VNorm(distance);

		//戻す量を計算、加算する

		VECTOR returnPosition = VScale(distance, (r - ReturnRange));

		position = VAdd(position, returnPosition);
	}

}
void PlayerBase::Draw() const
{
	MV1DrawModel(model_handle);
	bullet_manager->Draw();
}