#include"DxLib.h"
#include <math.h>
#include"Input.hpp"
#include"Camera.hpp"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
    :OriginalOffset(VGet(0, 0, 0))
    , position(VGet(0, 0, 0))
    , targetPosition(VGet(0, 0, 0))
    , AngleVec(VGet(0, 0, 0))
    , camera_dir(VGet(0, 0, 0))
    , isShake(false)
    , isDamage(true)
    , shakeTime(0)
    , angleHorizontal(0)
    , angleVertical(0)
{
    //垂直角度は0度
    angleVertical = 0.0f;
    //パースの設定
    SetupCamera_Perspective(70.0f * DX_PI_F / 180.0f);
    //奥行0.25～400までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 400.0f);
    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
    // 処理なし.
}

void Camera::Update(VECTOR playerPos)
{
    // カメラの目線の位置
    position = VAdd(playerPos, VGet(0.0f, CameraPlayerTargetHeight, 0.0f));
    // マウスによる回転
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    angleHorizontal += (mouseX - 960) * 0.001f;
    angleVertical += (mouseY - 540) * -0.001f;
    SetMousePoint(960, 540);

    // 垂直角度制限
    float maxPitch = DX_PI_F / 2 - 0.1f;
    if (angleVertical > maxPitch) angleVertical = maxPitch;
    if (angleVertical < -maxPitch) angleVertical = -maxPitch;
    //printfDx("cameraxpos%f\n", position.x);
    //printfDx("camerazpos%f\n", position.z);

    // 「←」ボタンが押されていたら水平角度をマイナスする
    if (rightInput->IsInputAnalogKey(Input::AnalogLeft))
    {
        angleHorizontal += AngleSpeed;

        // －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
        if (angleHorizontal > DX_PI_F)
        {
            angleHorizontal -= DX_TWO_PI_F;
        }
    }

    // 「→」ボタンが押されていたら水平角度をプラスする
    if (rightInput->IsInputAnalogKey(Input::AnalogRight))
    {
        angleHorizontal -= AngleSpeed;

        // １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
        if (angleHorizontal < -DX_PI_F)
        {
            angleHorizontal += DX_TWO_PI_F;
        }
    }

    // 「↑」ボタンが押されていたら垂直角度をマイナスする
    if (rightInput->IsInputAnalogKey(Input::AnalogUp))
    {
        angleVertical += AngleSpeed;

        //// ある一定角度以下にはならないようにする
        if (angleVertical > DX_PI_F * 0.5f - 0.6f)
        {
            angleVertical = DX_PI_F * 0.5f - 0.6f;
        }
    }

    // 「↓」ボタンが押されていたら垂直角度をプラスする
    if (rightInput->IsInputAnalogKey(Input::AnalogDown))
    {
        angleVertical -= AngleSpeed;

        //// ある一定角度以上にはならないようにする
        if (angleVertical < -DX_PI_F * 0.5f + 0.6f)
        {
            angleVertical = -DX_PI_F * 0.5f + 0.6f;
        }
    }
    camera_dir.x = cosf(angleVertical) * sinf(angleHorizontal);
    camera_dir.y = sinf(angleVertical);
    camera_dir.z = cosf(angleVertical) * cosf(angleHorizontal);

    targetPosition = VAdd(position, camera_dir);
    SetCameraPositionAndTarget_UpVecY(position, targetPosition);

}

void Camera::UpdateClear(const VECTOR& pos)
{
    // カメラの目線の位置を初期化
    position = VGet(0,2.0f,10.0f);
    // カメラのターゲット位置を初期化
    targetPosition = pos;

    SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

void Camera::UpdateTitle(const VECTOR& pos)
{
    // カメラの目線の位置を初期化
    position = VGet(-3.0f, 0.50f, 8.0f);
    // カメラのターゲット位置を初期化
    targetPosition = VAdd(pos, VGet(-3.0f,0,0));
    SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

void Camera::UpdateGameOver(const VECTOR& pos)
{
    // カメラの目線の位置を初期化
    position = VGet(-3.0f, 3.0f, 5.0f);
    // カメラのターゲット位置を初期化
    targetPosition = pos;
    SetCameraPositionAndTarget_UpVecY(position, targetPosition);
}

void Camera::FixCameraPosition()
{
}