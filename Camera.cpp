#include "stdafx.hpp"

#include"Window.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include"Input.hpp"
#include"Camera.hpp"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
    :OriginalOffset(VGet(0, 0, 0))
    , camera_position(VGet(0, 0, 0))
    , camera_targetpos(VGet(0, 0, 0))
    , camera_angle(VGet(0, 0, 0))
    , camera_dirction(VGet(0, 0, 0))
    , isShake(false)
    , isDamage(true)
    , shakeTime(0)
    , angleHorizontal(0)
    , angleVertical(0)
{
    obj_name = "Camera";


    //垂直角度は0度
    angleVertical = 0.0f;
    //パースの設定
    SetupCamera_Perspective(70.0f * DX_PI_F / 180.0f);
    //奥行0.25～400までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 400.0f);
    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(camera_position, camera_targetpos);

}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
    // 処理なし.
}

void Camera::Initialize()
{

}

void Camera::Update()
{
    // カメラの目線の位置
    camera_position = VAdd(player->GetPosition(), VGet(0.0f, CAMERA_PLAYERTARGET_HIGHT, 0.0f));
    
    // マウスによる回転
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    angleHorizontal += (mouseX - (WindowWidth /2)) * 0.001f;
    angleVertical += (mouseY - (WindowHight /2)) * -0.001f;
    SetMousePoint((WindowWidth /2), (WindowHight /2));

    // 垂直角度制限
    float maxPitch = DX_PI_F / 2 - 0.1f;
    if (angleVertical > maxPitch) angleVertical = maxPitch;
    if (angleVertical < -maxPitch) angleVertical = -maxPitch;
    //printfDx("cameraxpos%f\n", camera_position.x);
    //printfDx("camerazpos%f\n", camera_position.z);

    //// 「←」ボタンが押されていたら水平角度をマイナスする
    //if (rightInput->IsInputAnalogKey(Input::AnalogLeft))
    //{
    //    angleHorizontal += ANGLE_SPEED;

    //    // －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
    //    if (angleHorizontal > DX_PI_F)
    //    {
    //        angleHorizontal -= DX_TWO_PI_F;
    //    }
    //}

    //// 「→」ボタンが押されていたら水平角度をプラスする
    //if (rightInput->IsInputAnalogKey(Input::AnalogRight))
    //{
    //    angleHorizontal -= ANGLE_SPEED;

    //    // １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
    //    if (angleHorizontal < -DX_PI_F)
    //    {
    //        angleHorizontal += DX_TWO_PI_F;
    //    }
    //}

    //// 「↑」ボタンが押されていたら垂直角度をマイナスする
    //if (rightInput->IsInputAnalogKey(Input::AnalogUp))
    //{
    //    angleVertical += ANGLE_SPEED;

    //    //// ある一定角度以下にはならないようにする
    //    if (angleVertical > DX_PI_F * 0.5f - 0.6f)
    //    {
    //        angleVertical = DX_PI_F * 0.5f - 0.6f;
    //    }
    //}

    //// 「↓」ボタンが押されていたら垂直角度をプラスする
    //if (rightInput->IsInputAnalogKey(Input::AnalogDown))
    //{
    //    angleVertical -= ANGLE_SPEED;

    //    //// ある一定角度以上にはならないようにする
    //    if (angleVertical < -DX_PI_F * 0.5f + 0.6f)
    //    {
    //        angleVertical = -DX_PI_F * 0.5f + 0.6f;
    //    }
    //}
    camera_dirction.x = cosf(angleVertical) * sinf(angleHorizontal);
    camera_dirction.y = sinf(angleVertical);
    camera_dirction.z = cosf(angleVertical) * cosf(angleHorizontal);

    camera_targetpos = VAdd(camera_position, camera_dirction);
    SetCameraPositionAndTarget_UpVecY(camera_position, camera_targetpos);

}

void Camera::Draw()
{

}


void Camera::UpdateClear(const VECTOR& pos)
{
    // カメラの目線の位置を初期化
    camera_position = VGet(0,2.0f,10.0f);
    // カメラのターゲット位置を初期化
    camera_targetpos = pos;

    SetCameraPositionAndTarget_UpVecY(camera_position, camera_targetpos);
}

void Camera::UpdateTitle(const VECTOR& pos)
{
    // カメラの目線の位置を初期化
    camera_position = VGet(-3.0f, 0.50f, 8.0f);
    // カメラのターゲット位置を初期化
    camera_targetpos = VAdd(pos, VGet(-3.0f,0,0));
    SetCameraPositionAndTarget_UpVecY(camera_position, camera_targetpos);
}

void Camera::UpdateGameOver(const VECTOR& pos)
{
    // カメラの目線の位置を初期化
    camera_position = VGet(-3.0f, 3.0f, 5.0f);
    // カメラのターゲット位置を初期化
    camera_targetpos = pos;
    SetCameraPositionAndTarget_UpVecY(camera_position, camera_targetpos);
}

void Camera::FixCameraPosition()
{
}