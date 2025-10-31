#include "stdafx.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Input.hpp"

using json = nlohmann::json;

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
    OriginalOffset=VGet(0,0,0);
    obj_position=VGet(0,0,0);
    camera_targetpos=VGet(0,0,0);
    camera_angle=VGet(0,0,0);
    camera_dirction=VGet(0,0,0);
    isShake=false;
    isDamage = true;
    shakeTime=0;
    camera_angle_horizontal=0;
    camera_angle_virtual=0;

    obj_name = "Camera";

    //垂直角度は0度
    camera_angle_virtual = 0.0f;
    //パースの設定
    SetupCamera_Perspective(CAMERA_FOV * DX_PI_F / 180.0f);
    //奥行0.25～400までをカメラの描画範囲とする
    SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(obj_position, camera_targetpos);

}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
    // 処理なし.
}
/// <summary>
/// 初期化
/// </summary>
void Camera::Initialize()
{

}

void Camera::UpdateTitle()
{
    if (!enemy) return;

    // 目標: 敵の少し後方( -Z ) かつ少し上
    const VECTOR targetFocus = VAdd(enemy->GetPosition(), VGet(0.0f, 1.0f, 0.0f));
    const VECTOR targetCamPos = VAdd(targetFocus, VGet(-3.0f, 1.0f, -7.50f));

    // 現在位置 -> 目標位置を補間 (t は固定 0.1f で十分な減衰)
    obj_position = Lerp(obj_position, targetCamPos, 0.01f);
    camera_targetpos = Lerp(camera_targetpos, targetFocus, 0.01f);

    // 向きベクトル更新 (必要なら)
    camera_dirction = VSub(camera_targetpos, obj_position);

    SetCameraPositionAndTarget_UpVecY(obj_position, camera_targetpos);
}

/// <summary>
/// 更新
/// </summary>
void Camera::Update()
{

    // カメラの目線の位置
    obj_position = VAdd(player->GetPosition(), VGet(0.0f, CAMERA_PLAYERTARGET_HIGHT, 0.0f));
    
    // マウスによる回転
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    camera_angle_horizontal += (mouseX - (SCREEN_WIDTH /2)) * 0.001f;
    camera_angle_virtual += (mouseY - (SCREEN_HEIGHT /2)) * -0.001f;
    SetMousePoint((SCREEN_WIDTH /2), (SCREEN_HEIGHT /2));

    // 垂直角度制限
    float maxPitch = DX_PI_F / 2 - 0.1f;
    if (camera_angle_virtual > maxPitch) camera_angle_virtual = maxPitch;
    if (camera_angle_virtual < -maxPitch) camera_angle_virtual = -maxPitch;
    //printfDx("cameraxpos%f\n", obj_position.x);
    //printfDx("camerazpos%f\n", obj_position.z);

    // 「←」ボタンが押されていたら水平角度をマイナスする
    if (rightInput->IsInputAnalogKey(Input::AnalogLeft))
    {
        camera_angle_horizontal += ANGLE_SPEED;

        // －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
        if (camera_angle_horizontal > DX_PI_F)
        {
            camera_angle_horizontal -= DX_TWO_PI_F;
        }
    }

    // 「→」ボタンが押されていたら水平角度をプラスする
    if (rightInput->IsInputAnalogKey(Input::AnalogRight))
    {
        camera_angle_horizontal -= ANGLE_SPEED;

        // １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
        if (camera_angle_horizontal < -DX_PI_F)
        {
            camera_angle_horizontal += DX_TWO_PI_F;
        }
    }

    // 「↑」ボタンが押されていたら垂直角度をマイナスする
    if (rightInput->IsInputAnalogKey(Input::AnalogUp))
    {
        camera_angle_virtual += ANGLE_SPEED;

        //// ある一定角度以下にはならないようにする
        if (camera_angle_virtual > DX_PI_F * 0.5f - 0.6f)
        {
            camera_angle_virtual = DX_PI_F * 0.5f - 0.6f;
        }
    }

    // 「↓」ボタンが押されていたら垂直角度をプラスする
    if (rightInput->IsInputAnalogKey(Input::AnalogDown))
    {
        camera_angle_virtual -= ANGLE_SPEED;

        //// ある一定角度以上にはならないようにする
        if (camera_angle_virtual < -DX_PI_F * 0.5f + 0.6f)
        {
            camera_angle_virtual = -DX_PI_F * 0.5f + 0.6f;
        }
    }
    camera_dirction.x = cosf(camera_angle_virtual) * sinf(camera_angle_horizontal);
    camera_dirction.y = sinf(camera_angle_virtual);
    camera_dirction.z = cosf(camera_angle_virtual) * cosf(camera_angle_horizontal);

    camera_targetpos = VAdd(obj_position, camera_dirction);
    SetCameraPositionAndTarget_UpVecY(obj_position, camera_targetpos);

}

VECTOR Camera::Lerp(const VECTOR& camera_pos, const VECTOR& target_pos, float dampling)
{
    // t を 0-1 にクランプ (念のため)
    float clamped = dampling;
    if (clamped < 0.0f) clamped = 0.0f; else if (clamped > 1.0f) clamped = 1.0f;
    return VAdd(camera_pos, VScale(VSub(target_pos, camera_pos), clamped));
}

/// <summary>
/// ゲームクリアシーン用：敵を注視しつつ滑らかに所定位置へ移動 (Lerp)
/// </summary>
void Camera::UpdateGameClear()
{
    if (!enemy) return;

    // 目標: 敵の少し後方( -Z ) かつ少し上
    const VECTOR targetFocus = VAdd(enemy->GetPosition(), VGet(0, 2.0f, 0));
    const VECTOR targetCamPos = VAdd(targetFocus, VGet(0.0f, 1.0f, -10.0f));

    // 現在位置 -> 目標位置を補間 (t は固定 0.1f で十分な減衰)
    obj_position = Lerp(obj_position, targetCamPos, 0.01f);
    camera_targetpos = Lerp(camera_targetpos, targetFocus,   0.01f);

    // 向きベクトル更新 (必要なら)
    camera_dirction = VSub(camera_targetpos, obj_position);

    SetCameraPositionAndTarget_UpVecY(obj_position, camera_targetpos);
}

/// <summary>
/// 
/// </summary>
void Camera::FixCameraPosition()
{
}