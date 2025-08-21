#include "Dxlib.h"
#include "EffekseerForDXLib.h"
#include "Pallet.hpp"
#include "Bullet.hpp"

Bullet::Bullet(const VECTOR& position, const VECTOR& direction , const float bullet_speed)
	:position(VGet(0,0,0))
	,direction(VGet(0,0,0))
	,bullet_speed(0)
{
	this->position = position;
	this->direction = direction;
	this->bullet_speed = bullet_speed;
	prev_positon = position;
	effect_handle = LoadEffekseerEffect("data/effekseer/effekseer/Effect/fire.efkefc", 0.02f);
	playingEffectHandle = PlayEffekseer3DEffect(effect_handle);
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, EffectScale, EffectScale, EffectScale);
}

Bullet::~Bullet() {

}

void Bullet::Initialize()
{
	bullet_isporn = false;
}

void Bullet::Update()
{
	direction = VNorm(direction);
	direction = VScale(direction, bullet_speed);
	position = VAdd(position, direction);
	PlayEffect();
}

bool Bullet::CheckBulletOut()
{
	float bullet_range = VSize(VSub(position, prev_positon));
	if ((bullet_range > BulletRange || bullet_range < -BulletRange))
	{
		StopEffekseer3DEffect(playingEffectHandle);
		return true; // 弾が範囲外に出た場合はtrueを返す
	} 
	return false; // 弾が範囲内にいる場合はfalseを返す
}

void Bullet::DeleteBullet(int num)
{
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	StopEffekseer3DEffect(playingEffectHandle);
	DeleteEffekseerEffect(playingEffectHandle);
}

void Bullet::Draw()
{
	//DrawSphere3D(position, 0.3f, 20, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);
}

void Bullet::PlayEffect()
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
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}