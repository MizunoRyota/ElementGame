#include "Dxlib.h"
#include "EffekseerForDXLib.h"
#include "Camera.hpp"
#include "Input.hpp"
#include "PlayerWindAttack.hpp"

PlayerWindAttack::PlayerWindAttack(int modelhandle)
	:PlayerAttackBase(modelhandle)
	, prevbullet_angle(VGet(0, 0, 0))
{
	effect_handle = LoadEffekseerEffect("data/effekseer/effekseer/Effect/wind.efkefc", 0.01f);

	for (int i = 0; i < BulletNum; i++)
	{
		bullet_position[i] = VGet(0, 0, 0);
		isshot[i] = false;
		shot_isout[i] = true;
		bullet_position[i] = MV1GetFramePosition(model_handle, flame_name);
		windeffect_handle[i] = PlayEffekseer3DEffect(effect_handle);
		SetScalePlayingEffekseer3DEffect(windeffect_handle[i], EffectScale, EffectScale, EffectScale);
	}
	AngleVec = (VGet(0, 0, 0));
}

PlayerWindAttack::~PlayerWindAttack()
{
}

void PlayerWindAttack::Initialize()
{
	for (int i = 0; i < BulletNum; i++)
	{
		bullet_position[i] = VGet(0, EffectHight, 0);
		SetPosPlayingEffekseer3DEffect(windeffect_handle[i], bullet_position[i].x, bullet_position[i].y, bullet_position[i].z);
		isshot[i] = false;
		shot_isout[i] = true;
	}
}

void PlayerWindAttack::Update(const Input& input, const Camera& camera)
{
	if (cooldown_timer > 0) {
		cooldown_timer--; // クールダウン経過
	}

	Attack(input, camera);
	
	UpdateBullet(input, camera);

	CheckOutBullet();
	PlayEffect();
}

void PlayerWindAttack::Attack(const Input& input, const Camera& camera)
{
	// クールダウン中は発射できない
	if (cooldown_timer > 0){
		return;
	}

	bool attackKey = (input.GetNowFrameInput() & PAD_INPUT_C) || (GetMouseInput() & MOUSE_INPUT_LEFT);

	if (attackKey)
	{
		for (int i = 0; i < BulletNum; i++)
		{
			if (!isshot[i])
			{
				bullet_startposition[i] = bullet_position[i];
				isshot[i] = true;
				shot_isout[i] = false;
				cooldown_timer = CooldownTime; // 撃ったらクールダウン開始
				break; // 一発撃ったらループ抜ける
			}
		}
	}
}

void PlayerWindAttack::PlayEffect()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	for (int i = 0; i < BulletNum; i++)
	{
	if (!effect_isplay)
	{
		StopEffekseer3DEffect(windeffect_handle[i]);
		windeffect_handle[i] = PlayEffekseer3DEffect(effect_handle);
		SetScalePlayingEffekseer3DEffect(windeffect_handle[i], EffectScale, EffectScale, EffectScale);

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
		SetPosPlayingEffekseer3DEffect(windeffect_handle[i], bullet_position[i].x, bullet_position[i].y, bullet_position[i].z);
	}
}

void PlayerWindAttack::UpdateBullet(const Input& input, const Camera& camera)
{
	for (int i = 0; i < BulletNum; i++)
	{
		if (!isshot[i] && shot_isout[i])
		{
			AngleVec = VGet(0, 0, 0);
			AngleVec = VNorm(camera.GetCameraDir());
			prevbullet_angle = AngleVec;
			bullet_position[i] = MV1GetFramePosition(model_handle, flame_name);
		}
		if (isshot[i] && shot_isout[i])
		{
			shot_isout[i] = false;
		}
		if (!shot_isout[i] && isshot[i])
		{
			AngleVec = prevbullet_angle;
			AngleVec = VScale(AngleVec, moveSpeed);
			bullet_position[i] = VAdd(bullet_position[i], AngleVec);
		}
	}
}

void PlayerWindAttack::CheckOutBullet()
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

void PlayerWindAttack::CoolDown()
{

}