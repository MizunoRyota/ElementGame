#include "stdafx.hpp"
#include "EffectCreator.hpp"

/// <summary>
/// Jsonの読み込み
/// </summary>
void EffectCreator::LoadJson()
{
	std::ifstream file{ "EffectCreator.json" };
	json effect_json_data = json::parse(file);

	auto effectList = effect_json_data["EffectList"];

	// 各エフェクト読み込み
	for (int load_i = 0; load_i < effectList.size(); load_i++) {
		std::string path = effectList[load_i]["Path"].get<std::string>();
		float scale = effectList[load_i]["Scale"].get<float>();
		effect_handles[load_i] = LoadEffekseerEffect(path.c_str(), scale);
	}
}

/// <summary>
/// 初期化
/// </summary>
void EffectCreator::Initialize()
{
	for (int effect_num = 0; effect_num < EFFECT_NUM; effect_num++)
	{
		StopLoop(static_cast<EffectType>(effect_num));
		loop_enabled[effect_num] = false;
		effect_handles[effect_num] = -1;
		loop_playing_handles[effect_num] = -1;
		loop_positions[effect_num] = VGet(0, 0, 0);
		loop_enabled2D[effect_num] = false;
		loop_playing_handles2D[effect_num] = -1;
		loop_positions2D[effect_num] = VGet(0, 0, 0);
	}
	LoadJson(); // JSON読み込み
}

/// <summary>
/// 更新
/// </summary>
void EffectCreator::Update()
{
	Effekseer_Sync3DSetting(); // カメラ/行列同期

	UpdateEffekseer3D();       // 再生中全更新
	UpdateEffekseer2D();       // 再生中全更新
}

/// <summary>
/// 描画
/// </summary>
void EffectCreator::Draw()
{
	DrawEffekseer2D(); // 全描画
	DrawEffekseer3D(); // 全描画
}

/// <summary>
/// 再生
/// </summary>
/// <param name="EffectType"></param>
/// <param name="position"></param>
void EffectCreator::Play(EffectType EffectType, const VECTOR& position)
{
	(void)PlayReturn(EffectType, position); // 使い捨て
}

/// <summary>
/// 3D空間で指定された位置にエフェクトを再生
/// </summary>
/// <param name="EffectType">再生するエフェクトの種類を指定します。</param>
/// <param name="position">エフェクトを再生する3D空間内の位置座標です。</param>
/// <returns>再生中のエフェクトのハンドル。エフェクトが未ロードの場合は-1を返します。</returns>
int EffectCreator::PlayReturn(EffectType EffectType, const VECTOR& position)
{
	Effekseer_Sync3DSetting();
	const int effect_playinghandle = effect_handles[(int)EffectType];
	if (effect_playinghandle < 0) return -1; // 未ロード
	const int playing = PlayEffekseer3DEffect(effect_playinghandle);
	SetPosPlayingEffekseer3DEffect(playing, position.x, position.y, position.z);

	return playing;
}

/// <summary>
/// 指定された位置でエフェクトをループ再生
/// </summary>
/// <param name="type">再生するエフェクトの種類。</param>
/// <param name="position">エフェクトを再生する3D空間上の位置。</param>
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
			SetPosPlayingEffekseer3DEffect(loop_playing_handles[index], position.x, position.y, position.z);
		}
	}
	else
	{
		SetPosPlayingEffekseer3DEffect(loop_playing_handles[index], position.x, position.y, position.z);
	}
}

/// <summary>
/// 指定された位置でエフェクトをループ再生
/// </summary>
/// <param name="type">再生するエフェクトの種類。</param>
/// <param name="position">エフェクトを再生する3D空間上の位置。</param>
void EffectCreator::PlayLoop2D(EffectType type, const VECTOR& position)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;
	loop_enabled2D[index] = true;
	loop_positions2D[index] = position;
	// 既に再生中でなければここで開始( Update でも開始されるがラグを無くす )
	if (loop_playing_handles2D[index] < 0)
	{
		int playHandle = effect_handles[index];
		if (playHandle >= 0)
		{
			loop_playing_handles2D[index] = PlayEffekseer2DEffect(playHandle);
			SetPosPlayingEffekseer2DEffect(loop_playing_handles2D[index], position.x, position.y, position.z);
		}
	}
	else
	{
		SetPosPlayingEffekseer2DEffect(loop_playing_handles2D[index], position.x, position.y, position.z);
	}
}

/// <summary>
/// 指定されたエフェクトタイプのループ再生を停止
/// </summary>
/// <param name="type">停止するエフェクトのタイプ。</param>
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

/// <summary>
/// 指定されたエフェクトタイプのループ再生を停止
/// </summary>
/// <param name="type">停止するエフェクトのタイプ。</param>
void EffectCreator::StopLoop2D(EffectType type)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;
	loop_enabled2D[index] = false;
	if (loop_playing_handles2D[index] >= 0)
	{
		StopEffekseer2DEffect(loop_playing_handles2D[index]);
		loop_playing_handles2D[index] = -1;
	}
}

/// <summary>
/// ループエフェクトの位置を設定
/// </summary>
/// <param name="type">エフェクトの種類を指定します。</param>
/// <param name="position">エフェクトを配置する3D空間上の位置ベクトルです。</param>
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

/// <summary>
/// ループエフェクトの位置を設定
/// </summary>
/// <param name="type">エフェクトの種類を指定します。</param>
/// <param name="position">エフェクトを配置する3D空間上の位置ベクトルです。</param>
void EffectCreator::SetLoopPosition2D(EffectType type, const VECTOR& position)
{
	int index = (int)type;
	if (index < 0 || index >= EFFECT_NUM) return;
	int& playingHandle = loop_playing_handles2D[index];
	loop_positions2D[index] = position;
	if (loop_playing_handles2D[index] >= 0)
	{
		// 再生が終了しているか監視
		if (IsEffekseer2DEffectPlaying(playingHandle) == -1)
		{
			// 再生し直す
			playingHandle = PlayEffekseer2DEffect(effect_handles[index]);
		}
		SetPosPlayingEffekseer2DEffect(loop_playing_handles[index], position.x, position.y, position.z);
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
