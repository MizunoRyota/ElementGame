#include "stdafx.hpp"
#include "EffectCreator.hpp"

void EffectCreator::Initialize()
{

	if (effect_initialized) return; // 多重初期化防止
	effect_initialized = true;
	effect_move_angle = 0;
	Effekseer_Sync3DSetting(); // カメラ同期

	for (int effect_num = 0; effect_num < EFFECT_NUM; effect_num++)
	{
		loop_enabled[effect_num] = false;
		effect_handles[effect_num] = -1;
		loop_playing_handles[effect_num] = -1;
		loop_positions[effect_num] =VGet(0,0,0);
	}

	// 各エフェクト読み込み（失敗すると -1 が残る）
	effect_handles[(int)EffectType::BulletStraight] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/fire.efkefc", 0.5f);
	effect_handles[(int)EffectType::BulletDiffusion] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/water.efkefc", 0.5f);
	effect_handles[(int)EffectType::BulletHoming] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/wind.efkefc", 0.5f);
	effect_handles[(int)EffectType::BulletSpecial] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/SpecialAttack.efkefc", 1.0f);
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
	effect_handles[(int)EffectType::EnemyTire] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/EnemyTire.efkefc", 3.0f);
	effect_handles[(int)EffectType::ReadyAttack] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/ReadyAttack.efkefc", 2.0f);
	effect_handles[(int)EffectType::Crystal] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/Crystal.efkefc", 3.0f);
	effect_handles[(int)EffectType::ChargeEnergy] = LoadEffekseerEffect("data/effekseer/effekseer/Effect/ChargeEnergy1.efkefc", 01.0f);
}

void EffectCreator::Update()
{
	Effekseer_Sync3DSetting(); // カメラ/行列同期

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
			//if (loop_playing_handles[index] >= 0)
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
	Effekseer_Sync3DSetting();
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;
	int& playingHandle = loop_playing_handles[index];
	loop_positions[index] = position;
	if (loop_playing_handles[index] >= 0)
	{
		// 再生が終了しているか監視
		if (IsEffekseer3DEffectPlaying(playingHandle) == -1)
		{
			// 再生し直す
			playingHandle = PlayEffekseer3DEffect(effect_handles[index]);
		}
		SetPosPlayingEffekseer3DEffect(loop_playing_handles[index], position.x, position.y, position.z);
	}
}

// ターゲット位置を向く (水平: Y軸回転 + 上下: X軸回転)
// 既存のヨー(左右)スムージング処理を活かしつつ、ピッチ(上下)は直接設定。
void EffectCreator::SetRotateEffect(EffectType type, const VECTOR& target)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;

	Effekseer_Sync3DSetting();

	// 現在位置からターゲットへの方向
	VECTOR currentPos = loop_positions[index];
	VECTOR dir = { target.x - currentPos.x, target.y - currentPos.y, target.z - currentPos.z };

	// 水平距離 (XZ 平面)
	float dx = dir.x;
	float dz = dir.z;
	float horizontalLenSq = dx * dx + dz * dz;
	if (horizontalLenSq < 0.0000001f) return; // ほぼ同位置なら回転不要

	// --- YAW (水平回転, Y軸) スムーズ補間 ---
	float targetYaw = static_cast<float>(atan2(dx, dz)); // 左手系(+Z前)で右回転対応
	float diffYaw = targetYaw - effect_move_angle;
	if (diffYaw < -DX_PI_F) diffYaw += DX_TWO_PI_F; else if (diffYaw > DX_PI_F) diffYaw -= DX_TWO_PI_F;
	if (diffYaw > 0.0f)
	{
		diffYaw -= ANGLE_SPEED;
		if (diffYaw < 0.0f) diffYaw = 0.0f;
	}
	else
	{
		diffYaw += ANGLE_SPEED;
		if (diffYaw > 0.0f) diffYaw = 0.0f;
	}
	effect_move_angle = targetYaw - diffYaw; // 更新後のヨー角

	// --- PITCH (上下回転, X軸) ---
	float horizontalLen = sqrtf(horizontalLenSq);
	float pitch = 0.0f;
	// 上を向くと負角度 (DXLib/Effekseer の X 回転は反時計で俯くので符号反転)
	pitch = static_cast<float>(atan2(dir.y, horizontalLen));

	if (loop_playing_handles[index] >= 0)
	{
		// Effekseer 回転順 Z→X→Y. 今回は Z=0, X=ピッチ, Y=ヨー+PI で前向き補正。
		SetRotationPlayingEffekseer3DEffect(loop_playing_handles[index], pitch, effect_move_angle + DX_PI_F, 0.0f);
	}
}

// 方向ベクトルそのものから回転を決定 (direction は正規化不要、内部で正規化使用)
void EffectCreator::SetRotateEffectDirection(EffectType type, const VECTOR& direction)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;
	Effekseer_Sync3DSetting();
	if (loop_playing_handles[index] < 0) return;

	// 水平成分
	float dx = direction.x;
	float dz = direction.z;
	float horizontalLenSq = dx * dx + dz * dz;
	if (horizontalLenSq < 1e-8f) return;
	float horizontalLen = sqrtf(horizontalLenSq);

	// ヨー(左右) : atan2(x, z) 左手系補正 + Effekseer時計回り符号反転不要 (既存実装と合わせる)
	float yawCW = -atan2f(dx, dz);
	// ピッチ(上下) : 上向きを負にしたい場合 -atan2(y, 水平長) 既存のレーザー向き仕様に合わせる
	float pitchCW = -atan2f(direction.y, horizontalLen);

	// 直接適用
	SetRotationPlayingEffekseer3DEffect(loop_playing_handles[index], pitchCW, yawCW + DX_PI_F, 0.0f);
}