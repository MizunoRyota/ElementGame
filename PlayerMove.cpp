#include "stdafx.hpp"
#include "PlayerMove.hpp"
#include "Camera.hpp"
#include "Input.hpp"

PlayerMove::PlayerMove()
{
	moveVec = VGet(0, 0, 0);
	move_angle = 0;
}

PlayerMove::~PlayerMove() {}

// 入力とカメラから移動量・角度・ダッシュエネルギーを更新
void PlayerMove::Update(std::shared_ptr<Input>& input, std::shared_ptr<Camera>& camera)
{
	VECTOR upMoveVec;      // カメラ前方向(水平)
	VECTOR leftMoveVec;    // カメラ左方向(水平)

	moveVec = VGet(0, 0, 0);
	UpdateMoveParameterWithPad(input, camera, upMoveVec, leftMoveVec, moveVec);
	DecreaseDashEnergy();
	MoveAngle(camera->GetCameraDir());
	Move(moveVec);
}

// パッド/キーボード入力から移動ベクトルを算出
void PlayerMove::UpdateMoveParameterWithPad(std::shared_ptr<Input>& input, std::shared_ptr<Camera>& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	upMoveVec = VSub(camera->GetCameraTarget(), camera->GetPosition());
	upMoveVec.y = 0.0f;
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	bool isPressMoveButton = false;

	// クールタイム中またはエネルギー枯渇時はダッシュ入力を無効化
	bool dashKey = (CheckHitKey(KEY_INPUT_LSHIFT) != 0);
	if (dash_cooldown > 0 || dash_energy <= 0)
	{
		move_is_dash = false;
	}
	else
	{
		move_is_dash = dashKey;
	}

	if ((input->GetNowFrameInput() & PAD_INPUT_LEFT) || (CheckHitKey(KEY_INPUT_A) != 0))
	{
		moveVec = VAdd(moveVec, leftMoveVec);
		isPressMoveButton = true;
	}
	else if ((input->GetNowFrameInput() & PAD_INPUT_RIGHT) || (CheckHitKey(KEY_INPUT_D) != 0))
	{
		moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));
		isPressMoveButton = true;
	}

	if ((input->GetNowFrameInput() & PAD_INPUT_UP) || (CheckHitKey(KEY_INPUT_W) != 0))
	{
		moveVec = VAdd(moveVec, upMoveVec);
		isPressMoveButton = true;
	}
	else if ((input->GetNowFrameInput() & PAD_INPUT_DOWN) || (CheckHitKey(KEY_INPUT_S) != 0))
	{
		moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));
		isPressMoveButton = true;
	}

	if (isPressMoveButton)
	{
		move_targetdirection = VNorm(moveVec);
		float speed = MOVE_SPEED * (move_is_dash && dash_energy > 0 && dash_cooldown == 0 ? DASH_MULTIPLIER : 1.0f);
		moveVec = VScale(move_targetdirection, speed);
	}
}

// ダッシュエネルギー/クールタイムの進行
void PlayerMove::DecreaseDashEnergy()
{
	// クールタイム中
	if (dash_cooldown > 0)
	{
		dash_cooldown--; // クールタイム経過
		return; // クール中は回復も消費もしない
	}

	if (move_is_dash && dash_energy > 0)
	{
		dash_energy -= DASH_DECREACE_NUM;
		if (dash_energy <= 0)
		{
			dash_energy = 0;
			dash_cooldown = DASH_COOLDOWN_FRAMES; // 枯渇でクールタイム開始
			move_is_dash = false;
		}
	}
	else
	{
		// 通常回復（クールタイムが終わっている時）
		if (dash_energy < DASH_MAXENERGY)
		{
			dash_energy++;
		}
	}
}

// 目標角へなめらかに追従
void PlayerMove::MoveAngle(const VECTOR& targetPosition)
{
	float targetAngle = static_cast<float>(atan2(targetPosition.x, targetPosition.z));
	float difference = targetAngle - move_angle;
	if (difference < -DX_PI_F) difference += DX_TWO_PI_F; else if (difference > DX_PI_F) difference -= DX_TWO_PI_F;
	if (difference > 0.0f)
	{
		difference -= ANGLE_SPEED;
		if (difference < 0.0f) difference = 0.0f;
	}
	else
	{
		difference += ANGLE_SPEED;
		if (difference > 0.0f) difference = 0.0f;
	}
	move_angle = targetAngle - difference;
}

// 実移動適用（移動したかどうかのフラグのみ）
void PlayerMove::Move(const VECTOR& MoveVector)
{
	move_is_move = (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f);
}