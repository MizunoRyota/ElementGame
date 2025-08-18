#include "Dxlib.h"
#include "EffekseerForDXLib.h"
#include "Camera.hpp"
#include "Input.hpp"
#include "PlayerWaterAttack.hpp"

PlayerWaterAttack::PlayerWaterAttack(int modelhandle)
	:PlayerAttackBase(modelhandle)

{
	effect_handle = LoadEffekseerEffect("data/effekseer/effekseer/Effect/water.efkefc", 0.01f);

	for (int i = 0; i < BulletNum; i++)
	{
		bullet_position[i] = VGet(0, 0, 0);
		isshot[i] = false;
		shot_isout[i] = true;
		bullet_position[i] = MV1GetFramePosition(model_handle, flame_name);
		watereffect_handle[i] = PlayEffekseer3DEffect(effect_handle);
		SetScalePlayingEffekseer3DEffect(watereffect_handle[i], EffectScale, EffectScale, EffectScale);
	}
	AngleVec = (VGet(0, 0, 0));
}

PlayerWaterAttack::~PlayerWaterAttack()
{

}
void PlayerWaterAttack::Initialize()
{
    for (int i = 0; i < BulletNum; i++)
    {
        bullet_position[i] = VGet(0, EffectHight, 0);
        SetPosPlayingEffekseer3DEffect(watereffect_handle[i], bullet_position[i].x, bullet_position[i].y, bullet_position[i].z);
        isshot[i] = false;
        shot_isout[i] = true;
    }
}

void PlayerWaterAttack::Update(const Input& input, const Camera& camera)
{
    if (cooldown_timer > 0) {
        cooldown_timer--; // クールダウン経過
    }

    Attack(input, camera);

    UpdateBullet(input, camera);

    CheckOutBullet();
    PlayEffect();
}
void PlayerWaterAttack::Attack(const Input& input, const Camera& camera)
{
    if (cooldown_timer > 0) return; // クールダウン中は撃てない

    bool attackKey = (input.GetNowFrameInput() & PAD_INPUT_C) || (GetMouseInput() & MOUSE_INPUT_LEFT);
    if (attackKey)
    {
        // カメラの向き（前方ベクトル）
        VECTOR forward = camera.GetCameraDir(); // 仮：カメラの前方を返す関数を想定
        forward = VNorm(forward); // 正規化

        // 放射状の角度差（ラジアン）
        constexpr float angleOffset = DX_PI_F / 54.0f; // 約10度

        // 発射する3方向ベクトルを作る
        VECTOR directions[BulletNum];
        directions[0] = forward; // 中央

        // 左右方向のベクトルを作る（Y軸を基準に回転）
        MATRIX rotLeft = MGetRotY(-angleOffset);
        MATRIX rotRight = MGetRotY(angleOffset);

        directions[1] = VTransform(forward, rotLeft);  // 左
        directions[2] = VTransform(forward, rotRight); // 右

        // 3発撃つ
        for (int j = 0; j < BulletNum; j++)
        {
            for (int i = 0; i < BulletNum; i++)
            {
                if (!isshot[i]) // 空いてる弾スロットを使う
                {
                    bullet_position[i] = MV1GetFramePosition(model_handle, flame_name);
                    bullet_startposition[i] = bullet_position[i];
                    prevbullet_angle[i] = directions[j];
                    isshot[i] = true;
                    shot_isout[i] = false;
                    break;
                }
            }
        }

        // クールダウン開始
        cooldown_timer = CooldownTime;
    }
}

void PlayerWaterAttack::PlayEffect()
{
    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();

    for (int i = 0; i < BulletNum; i++)
    {
        if (!effect_isplay)
        {
            StopEffekseer3DEffect(watereffect_handle[i]);
            watereffect_handle[i] = PlayEffekseer3DEffect(effect_handle);
            SetScalePlayingEffekseer3DEffect(watereffect_handle[i], EffectScale, EffectScale, EffectScale);

            //エフェクトを再生する
            effect_isplay = true;
            effect_isend = false;
        }
        else
        {
            time += PlayEffectSpeed;
            if (time >= EndTime) // 30フレーム経過したらエフェクトを終了
            {
                effect_isend = true;
                effect_isplay = false;
                time = 0; // 時間をリセット
            }
        }
        SetPosPlayingEffekseer3DEffect(watereffect_handle[i], bullet_position[i].x, bullet_position[i].y, bullet_position[i].z);
    }

}

void PlayerWaterAttack::UpdateBullet(const Input& input, const Camera& camera)
{
    for (int i = 0; i < BulletNum; i++)
    {
        if (!isshot[i] && shot_isout[i])
        {
            AngleVec = VGet(0, 0, 0);
            AngleVec = VNorm(camera.GetCameraDir());
            prevbullet_angle[i] = AngleVec;
            bullet_position[i] = MV1GetFramePosition(model_handle, flame_name);
        }
        if (isshot[i] && shot_isout[i])
        {
            shot_isout[i] = false;
        }
        if (!shot_isout[i] && isshot[i])
        {
            AngleVec = prevbullet_angle[i];
            AngleVec = VScale(AngleVec, moveSpeed);
            bullet_position[i] = VAdd(bullet_position[i], AngleVec);
        }
    }
}

void PlayerWaterAttack::CheckOutBullet()
{
    for (int i = 0; i < BulletNum; i++)
    {
        float bullet_range = VSize(VSub(bullet_position[i], bullet_startposition[i]));
        if (bullet_range > BulletRange || bullet_range < -BulletRange)
        {
            isshot[i] = false;
            shot_isout[i] = true;
        }
    }
}

void PlayerWaterAttack::CoolDown()
{

}