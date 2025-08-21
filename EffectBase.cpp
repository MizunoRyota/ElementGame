#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffectBase.hpp"

EffectBase::EffectBase()
	:position(VGet(0.0f,0.0f,0.0f))
	,time(0)
	,effectHandle(0)
	,playingEffectHandle(0)
	,effect_isplay(false)
	,effect_isend(false)
{
	StageEffect = LoadEffekseerEffect("data/effekseer/effekseer/EfkFile/GroundFire.efkefc",EffectScale);
}

EffectBase::~EffectBase()
{
}

void EffectBase::Update(const VECTOR& position)
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	//エフェクト再生
	PlayEffect();

	//エフェクトの位置設定
	SetPosition(position);

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void EffectBase::SetPosition(const VECTOR& Position)
{
	SetPosPlayingEffekseer3DEffect(playingEffectHandle,position.x,EffectHight,position.z);
}

void EffectBase::PlayEffect()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	if (!effect_isplay)
	{
		//エフェクトを再生する
		effect_isplay = true;
		effect_isend = false;
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(StageEffect);
	}
	else
	{
		time+=PlayEffectSpeed;
		if (time >= EndTime) // 30フレーム経過したらエフェクトを終了
		{
			effect_isend = true;
			effect_isplay = false;
			time = 0; // 時間をリセット
		}
	}
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, EffectHight, position.z);

}

void EffectBase::DrawEffect()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}