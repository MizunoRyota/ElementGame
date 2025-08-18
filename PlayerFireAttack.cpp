#include "Dxlib.h"
#include "EffekseerForDXLib.h"
#include "Camera.hpp"
#include "Input.hpp"
#include "PlayerFireAttack.hpp"

PlayerFireAttack::PlayerFireAttack(int modelhadle)
	:PlayerAttackBase(modelhadle)
	, bullet_position(VGet(0, 0, 0))
	, bullet_startposition(VGet(0, 0, 0))
	, isshot(false)
	,shot_isout(true)
	,prevbullet_angle(VGet(0,0,0))
{
	effect_handle = LoadEffekseerEffect("data/effekseer/effekseer/Effect/fire.efkefc", 0.02f);
	playingEffectHandle = PlayEffekseer3DEffect(effect_handle);
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, EffectScale, EffectScale, EffectScale);

	AngleVec = (VGet(0, 0, 0));
	bullet_position = MV1GetFramePosition(model_handle, flame_name);

}

PlayerFireAttack::~PlayerFireAttack()
{
}

void PlayerFireAttack::Initialize()
{
	bullet_position = VGet(0, EffectHight, 0);
	isshot = false;
	shot_isout = true;
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, bullet_position.x, bullet_position.y, bullet_position.z);
}

void PlayerFireAttack::Update(const Input& input, const Camera& camera)
{
	if ((!input.GetNowFrameInput() & PAD_INPUT_C) == 0 && (!GetMouseInput() &MOUSE_INPUT_LEFT) == 0)
	{
		Attack(input, camera);
	}
	UpdateBullet(input,camera);

	CheckOutBullet();
	PlayEffect();
}

void PlayerFireAttack::CheckOutBullet()
{
	float bullet_range = VSize(VSub(bullet_position, bullet_startposition));
	if (bullet_range > BulletRange || bullet_range < -BulletRange)
	{
		isshot = false;
		shot_isout = true;
	}
}

void PlayerFireAttack::Attack(const Input& input, const Camera& camera)
{
	if (!isshot)
	{
		bullet_startposition = bullet_position;
	}
	isshot = true;
}

void PlayerFireAttack::UpdateBullet(const Input& input, const Camera& camera)
{
	if (!isshot && shot_isout)
	{
		AngleVec = VGet(0, 0, 0);
		AngleVec = VNorm(camera.GetCameraDir());
		prevbullet_angle = AngleVec;
		bullet_position = MV1GetFramePosition(model_handle, flame_name);
	}
	if (isshot && shot_isout)
	{
		shot_isout = false;
	}
	if (!shot_isout && isshot)
	{
		AngleVec = prevbullet_angle;
		AngleVec = VScale(AngleVec, moveSpeed);
		bullet_position = VAdd(bullet_position, AngleVec);
	}
}

void PlayerFireAttack::PlayEffect()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	if (!effect_isplay)
	{
		StopEffekseer3DEffect(playingEffectHandle);

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
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, bullet_position.x, bullet_position.y, bullet_position.z);
}

void PlayerFireAttack::CoolDown()
{

}