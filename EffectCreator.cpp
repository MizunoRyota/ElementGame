#include "stdafx.hpp"
#include "EffectCreator.hpp"

void EffectCreator::Initialize()
{

	if (effect_initialized) return; // 多重初期化防止
	effect_initialized = true;

	Effekseer_Sync3DSetting(); // カメラ同期

	// 各エフェクト読み込み（失敗すると -1 が残る）
	effect_handles[(int)EffectType::BulletStraight] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/fire.efkefc", 0.3f);
	effect_handles[(int)EffectType::BulletDiffusion] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/water.efkefc", 0.3f);
	effect_handles[(int)EffectType::BulletHoming] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/wind.efkefc", 0.2f);
	effect_handles[(int)EffectType::BulletSpecial] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/SpecialAttack.efkefc", 0.40f);
	effect_handles[(int)EffectType::BulletHit] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/Hit.efkefc", 0.15f);
	effect_handles[(int)EffectType::FireGround] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/FireGround.efkefc", 4.5f);
	effect_handles[(int)EffectType::EnemyDeath] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/BossDeath.efkefc", 1.0f);
	effect_handles[(int)EffectType::EnemyCharge] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/Charge.efkefc", 3.5f);
	effect_handles[(int)EffectType::Laser] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/Laser.efkefc", 0.10f);
	effect_handles[(int)EffectType::Roar] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/Roar.efkefc", 3.5f);
	effect_handles[(int)EffectType::FireWorks] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/FireWorks.efkefc", 0.5f);
	effect_handles[(int)EffectType::HandEffect] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/hand_effect.efkefc", 0.04f);
	effect_handles[(int)EffectType::HandCharge] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/hand_charge.efkefc", 0.04f);
	effect_handles[(int)EffectType::Barrior] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/Barrior.efkefc", 1.2f);
	effect_handles[(int)EffectType::BulletPlayer] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/player_attack.efkefc", 0.3f);
	effect_handles[(int)EffectType::BreakCrystal] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/breakCrystal.efkefc", 2.0f);
}

void EffectCreator::Update()
{
	Effekseer_Sync3DSetting(); // カメラ/行列同期

	//// ループ再生チェック
	for (int i = 0; i < EFFECT_NUM; ++i)
	{
		if (!loop_enabled[i]) continue;
		int& playingHandle = loop_playing_handles[i];
		if (playingHandle >= 0)
		{
			// 再生が終了しているか監視
			if (IsEffekseer3DEffectPlaying(playingHandle) == -1)
			{
				// 再生し直す
				playingHandle = PlayEffekseer3DEffect(effect_handles[i]);
				if (playingHandle >= 0)
				{
					SetPosPlayingEffekseer3DEffect(playingHandle, loop_positions[i].x, loop_positions[i].y, loop_positions[i].z);
				}
			}
		}
		else
		{
			// まだ開始していない(初回)
			playingHandle = PlayEffekseer3DEffect(effect_handles[i]);
			if (playingHandle >= 0)
			{
				SetPosPlayingEffekseer3DEffect(playingHandle, loop_positions[i].x, loop_positions[i].y, loop_positions[i].z);
			}
		}
	}

	UpdateEffekseer3D();       // 再生中全更新

}

void EffectCreator::Draw()
{
	DrawEffekseer3D(); // 全描画
}

void EffectCreator::Play(EffectType EffectType, const VECTOR& position)
{
	(void)PlayReturn(EffectType, position); // 使い捨て
}

int EffectCreator::PlayReturn(EffectType EffectType, const VECTOR& position)
{
	Effekseer_Sync3DSetting();
	const int effect_playinghandle = effect_handles[(int)EffectType];
	if (effect_playinghandle < 0) return -1; // 未ロード
	const int playing = PlayEffekseer3DEffect(effect_playinghandle);
	SetPosPlayingEffekseer3DEffect(playing, position.x, position.y, position.z);
	return playing;
}

void EffectCreator::PlayLoop(EffectType type, const VECTOR& position)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;
	loop_enabled[index] = true;
	loop_positions[index] = position;
	// 既に再生中でなければここで開始( Update でも開始されるがラグを無くす )
	if (loop_playing_handles[index] < 0)
	{
		int playHandle = effect_handles[index];
		if (playHandle >= 0)
		{
			loop_playing_handles[index] = PlayEffekseer3DEffect(playHandle);
			if (loop_playing_handles[index] >= 0)
			SetPosPlayingEffekseer3DEffect(loop_playing_handles[index], position.x, position.y, position.z);
		}
	}
	else
	{
		SetPosPlayingEffekseer3DEffect(loop_playing_handles[index], position.x, position.y, position.z);
	}
}

void EffectCreator::StopLoop(EffectType type)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;
	loop_enabled[index] = false;
	if (loop_playing_handles[index] >= 0)
	{
		StopEffekseer3DEffect(loop_playing_handles[index]);
		loop_playing_handles[index] = -1;
	}
}

void EffectCreator::SetLoopPosition(EffectType type, const VECTOR& position)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;
	loop_positions[index] = position;
	if (loop_playing_handles[index] >= 0)
	{
		SetPosPlayingEffekseer3DEffect(loop_playing_handles[index], position.x, position.y, position.z);
	}
}

void EffectCreator::SetRotateEffect(EffectType type, const VECTOR& dir)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;

	float dirction = VSquareSize(dir);

	if (loop_playing_handles[index] >= 0)
	{
		SetRotationPlayingEffekseer3DEffect(loop_playing_handles[index], dir.y, -dir.x, dir.z);
	}
}