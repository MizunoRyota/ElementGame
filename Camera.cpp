#include "stdafx.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "ObjectAccessor.hpp"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
    OriginalOffset=VGet(0,0,0);
    obj_position=VGet(0,0,0);
    camera_targetpos=VGet(0,0,0);
    camera_angle=VGet(0,0,0);
    obj_direction=VGet(0,0,0);
    camera_shake=false;
    camera_shaketime=0;
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
    camera_shake = false;
    camera_shaketime = 0.0f;
    // カメラの目線の位置
    obj_position = VAdd(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), VGet(0.0f, CAMERA_PLAYERTARGET_HIGHT, 0.0f));
    obj_direction = VGet(0.0f, 0.0f, 1.0f);
    camera_angle_horizontal = 0;
    camera_angle_virtual = 0;
    camera_targetpos = VAdd(obj_position, obj_direction);

    SetCameraPositionAndTarget_UpVecY(obj_position, camera_targetpos);
}

void Camera::UpdateTitle()
{

    // 目標: 敵の少し後方( -Z ) かつ少し上
    const VECTOR targetFocus = VAdd(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), VGet(-3.0f, 1.0f, 0.0f));
    const VECTOR targetCamPos = VAdd(targetFocus, VGet(-3.0f, 1.0f, -3.50f));

    // 現在位置 -> 目標位置を補間 (t は固定 0.1f で十分な減衰)
    obj_position = Lerp(obj_position, targetCamPos, 0.01f);
    camera_targetpos = Lerp(camera_targetpos, targetFocus, 0.01f);

    // 向きベクトル更新 (必要なら)
    obj_direction = VSub(camera_targetpos, obj_position);

    SetCameraPositionAndTarget_UpVecY(obj_position, camera_targetpos);
}

void Camera::UpdateForMouse()
{
    int mouseX = 0, mouseY = 0;
    GetMousePoint(&mouseX, &mouseY);
    camera_angle_horizontal += (mouseX - (SCREEN_WIDTH / HARF)) * 0.001f;
    camera_angle_virtual += (mouseY - (SCREEN_HEIGHT / HARF)) * -0.001f;
    SetMousePoint((SCREEN_WIDTH / HARF), (SCREEN_HEIGHT / HARF));
}

void Camera::UpdateForController()
{

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
}

/// <summary>
/// 更新
/// </summary>
void Camera::Update()
{

    // カメラの目線の位置
    obj_position = VAdd(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), VGet(0.0f, CAMERA_PLAYERTARGET_HIGHT, 0.0f));

    ShakeCamera();

    // マウスによる回転
    if (ObjectAccessor::GetObjectAccessor().GetInputType() > 0)
    {
        UpdateForController();
    }
    else
    {
        UpdateForMouse();
    }
    // 垂直角度制限
    float maxPitch = DX_PI_F / HARF - 1.0f;
    if (camera_angle_virtual > maxPitch) camera_angle_virtual = maxPitch;
    if (camera_angle_virtual < -maxPitch) camera_angle_virtual = -maxPitch;

    obj_direction.x = cosf(camera_angle_virtual) * sinf(camera_angle_horizontal);
    obj_direction.y = sinf(camera_angle_virtual);
    obj_direction.z = cosf(camera_angle_virtual) * cosf(camera_angle_horizontal);

    camera_targetpos = VAdd(obj_position, obj_direction);
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

    // 目標: 敵の少し後方( -Z ) かつ少し上
    const VECTOR targetFocus = VAdd(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), VGet(0, 2.0f, 0));
    const VECTOR targetCamPos = VAdd(targetFocus, VGet(0.0f, 1.0f, -10.0f));

    // 現在位置 -> 目標位置を補間 (t は固定 0.1f で十分な減衰)
    obj_position = Lerp(obj_position, targetCamPos, 0.01f);
    camera_targetpos = Lerp(camera_targetpos, targetFocus,   0.01f);

    // 向きベクトル更新 (必要なら)
    obj_direction = VSub(camera_targetpos, obj_position);

    SetCameraPositionAndTarget_UpVecY(obj_position, camera_targetpos);
}


void Camera::StartShakeCamera()
{
    if (camera_shake)return;
    camera_shake = true;
    camera_shaketime = CAMERA_MAX_SHAKETIME;
}

/// <summary>
/// カメラをランダムに小刻みに揺らす（時間経過で減衰）
/// </summary>
void Camera::ShakeCamera()
{
    if (!camera_shake) return;

    // シェイク時間を減らす
    camera_shaketime -= CAMERA_SHAKESPEED;

    // 終了判定
    if (camera_shaketime <= 0.0f)
    {
        camera_shaketime = 0.0f;
        camera_shake = false;
        return;
    }

    // 残り時間に応じて振幅を減衰させる
    const float t = camera_shaketime / CAMERA_MAX_SHAKETIME; // 1.0 -> 0.0
    const float maxAmplitude = 0.30f; // 最大揺れ量（必要に応じて調整）
    const float amplitude = maxAmplitude * t;

    // -1.0f ～ 1.0f の乱数を生成
    auto randSign01 = []() -> float {
        return (static_cast<float>(GetRand(1000)) / 1000.0f) - 1.0f;
    };

    // 位置をランダムにオフセット（Z は控えめ）
    const float offX = randSign01() * amplitude;
    const float offY = randSign01() * amplitude;
    const float offZ = randSign01() * (amplitude * 0.5f);

    obj_position = VAdd(obj_position, VGet(offX, offY, offZ));
}

void Camera::Draw()
{
    if (ChengeDebugFlag())
    {
        SetLogDrawArea(0, 100, 600, 1000);
        setPrintColorDx(Pallet::DeepSkyBlue.GetHandle());
        printfDx("CameraPosition.x: %f", obj_position.x);
        printfDx(" y %f", obj_position.y);
        printfDx(" z %f\n\n", obj_position.z);
        printfDx("CameraDirection.x: %f", obj_direction.x);
        printfDx(" y %f", obj_direction.y);
        printfDx(" z %f\n\n", obj_direction.z);
    }
}