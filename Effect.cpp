#include "stdafx.hpp"
#include "Effect.hpp"

Effect::Effect(int effect_handle)
	:effect_isplay(false)
	,effect_isend(false)
	,effect_handle(0)
	,effect_playinghandle(-1)
	, effect_playtime(0)
	,effect_position(VGet(0,0,0))
{
	this->effect_handle = effect_handle;
	effect_playinghandle = PlayEffekseer3DEffect(this->effect_handle);

}

Effect::~Effect()
{
}

void Effect::Update(const VECTOR& position)
{

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	PlayEffect();

	SetPosition(position);



}

void Effect::UpdateEffect()
{
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void Effect::PlayEffect()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	if (!effect_isplay)
	{
		//エフェクトを再生する
		effect_isplay = true;
		effect_isend = false;
		// エフェクトを再生する。
		effect_playinghandle = PlayEffekseer3DEffect(effect_handle);
	}
	else
	{
		effect_playtime += EFFCT_PLAYSPEED;
		if (effect_playtime >= EFFECT_ENDTIME) // 30フレーム経過したらエフェクトを終了
		{
			effect_isend = true;
			effect_isplay = false;
			effect_playtime = 0; // 時間をリセット
		}
	}

}

void Effect::SetPosition(const VECTOR& position)
{
	SetPosPlayingEffekseer3DEffect(effect_playinghandle, position.x, position.y, position.z);
}

void Effect::DrawEffect()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}