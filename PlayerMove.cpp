#include <math.h>
#include"DxLib.h"
#include"PlayerMove.hpp"
#include"Camera.hpp"
#include"Input.hpp"
PlayerMove::PlayerMove()
	:moveVec(VGet(0,0,0))
	,angle	(0)
{
}

PlayerMove::~PlayerMove()
{
}

void PlayerMove::Update(const Input& input, const Camera& camera)
{
	// パッド入力によって移動パラメータを設定する
	VECTOR	upMoveVec;		// 方向ボタン「↑」を入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 方向ボタン「←」を入力をしたときのプレイヤーの移動方向ベクトル
	moveVec = VGet(0, 0, 0);
	UpdateMoveParameterWithPad(input, camera, upMoveVec, leftMoveVec, moveVec);	//プレイヤー座標更新処理

	MoveAngle(camera.GetCameraDir()); //プレイヤーが進む方向にモデルを回転

	// 移動ベクトルを元にコリジョンを考慮しつつプレイヤーを移動
	Move(moveVec);

}

void PlayerMove::UpdateMoveParameterWithPad(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{

	// プレイヤーの移動方向のベクトルを算出
	// 方向ボタン「↑」を押したときのプレイヤーの移動ベクトルはカメラの視線方向からＹ成分を抜いたもの
	upMoveVec = VSub(camera.GetTarget(), camera.GetPosition());
	upMoveVec.y = 0.0f;

	// 方向ボタン「←」を押したときのプレイヤーの移動ベクトルは上を押したときの方向ベクトルとＹ軸のプラス方向のベクトルに垂直な方向
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

	// 二つのベクトルを正規化( ベクトルの長さを１．０にすること )
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);

	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 移動したかどうかのフラグを初期状態では「移動していない」を表すFALSEにする
	bool isPressMoveButton = false;

	// パッドの３ボタンと左シフトがどちらも押されていなかったらプレイヤーの移動処理
	if (CheckHitKey(KEY_INPUT_LSHIFT) == 0)
	{
		// 方向ボタン「←」が入力されたらカメラの見ている方向から見て左方向に移動する
		if (input.GetNowFrameInput() & PAD_INPUT_LEFT || (CheckHitKey(KEY_INPUT_A) != 0))
		{
			// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
			moveVec = VAdd(moveVec, leftMoveVec);

			// 移動したかどうかのフラグを「移動した」にする
			isPressMoveButton = true;
		}
		else
			// 方向ボタン「→」が入力されたらカメラの見ている方向から見て右方向に移動する
			if (input.GetNowFrameInput() & PAD_INPUT_RIGHT || (CheckHitKey(KEY_INPUT_D) != 0))
			{
				// 移動ベクトルに「←」が入力された時の移動ベクトルを反転したものを加算する
				moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));

				// 移動したかどうかのフラグを「移動した」にする
				isPressMoveButton = true;
			}
	
		// 方向ボタン「↑」が入力されたらカメラの見ている方向に移動する
		if (input.GetNowFrameInput() & PAD_INPUT_UP || (CheckHitKey(KEY_INPUT_W) != 0))
		{

			// 移動ベクトルに「↑」が入力された時の移動ベクトルを加算する
			moveVec = VAdd(moveVec, upMoveVec);

			// 移動したかどうかのフラグを「移動した」にする
			isPressMoveButton = true;
		}
		else
			// 方向ボタン「↓」が入力されたらカメラの方向に移動する
			if (input.GetNowFrameInput() & PAD_INPUT_DOWN || (CheckHitKey(KEY_INPUT_S) != 0))
			{
				// 移動ベクトルに「↑」が入力された時の移動ベクトルを反転したものを加算する
				moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));

				// 移動したかどうかのフラグを「移動した」にする
				isPressMoveButton = true;
			}
	}
	// 移動ボタンが押されたかどうかで処理を分岐
	if (isPressMoveButton)
	{
		// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
		targetMoveDirection = VNorm(moveVec);

		// プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
		moveVec = VScale(targetMoveDirection, MoveSpeed);
	}
}

void PlayerMove::MoveAngle(const VECTOR& targetPosition)
{
	// プレイヤーの移動方向にモデルの方向を近づける
	float targetAngle;			// 目標角度
	float difference;			// 目標角度と現在の角度との差

	// 目標の方向ベクトルから角度値を算出する
	targetAngle = static_cast<float>(atan2(targetPosition.x, targetPosition.z));

	// 目標の角度と現在の角度との差を割り出す
	// 最初は単純に引き算
	difference = targetAngle - angle;

	// ある方向からある方向の差が１８０度以上になることは無いので
	// 差の値が１８０度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	// 角度の差が０に近づける
	if (difference > 0.0f)
	{
		// 差がプラスの場合は引く
		difference -= AngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		difference += AngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// モデルの角度を更新
	angle = targetAngle - difference;
}

void PlayerMove::Move(const VECTOR& MoveVector)
{
	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}
}