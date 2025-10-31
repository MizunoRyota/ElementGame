#pragma once
#include "stdafx.hpp"

// Effekseer を用いた 3D エフェクト管理（簡易）
class EffectCreator
{
public:
	enum class EffectType : int
	{
		BulletStraight,
		BulletDiffusion,
		BulletHoming, // 追尾弾
		BulletSpecial,
		BulletHit,
		FireGround,
		EnemyDeath,
		EnemyCharge,
		Laser,
		Roar,
		FireWorks,
		HandEffect,
		HandCharge,
		Barrior,
		BulletPlayer,
		BreakCrystal,
		EnemyTire,
	};

	static EffectCreator& GetEffectCreator()
	{
		static EffectCreator instance; // シングルトン
		return instance;
	}

	void Initialize();   // 初期化（エフェクト読み込み）
	void Update();       // フレーム更新（Effekseer更新）
	void Draw();         // 描画
	void Play(EffectType EffectType, const VECTOR& position); // 再生（即席）
	int  PlayReturn(EffectType EffectType, const VECTOR& position); // 再生ハンドル返却

	// ループ再生開始（StopLoop するまで繰り返し再生）
	void PlayLoop(EffectType type, const VECTOR& position);
	// ループ再生停止
	void StopLoop(EffectType type);
	// ループ再生中エフェクトの位置更新
	void SetLoopPosition(EffectType type, const VECTOR& position);

	void SetRotateEffect(EffectType type, const VECTOR& dir); // 回転設定

private:
	EffectCreator() = default;
	~EffectCreator() = default;
	EffectCreator(const EffectCreator&) = delete;
	EffectCreator& operator=(const EffectCreator&) = delete;

	static constexpr int   EFFECT_NUM = 17;          // 事前読み込み数
	static constexpr float EFFECT_HIGHT = 0.3f;      // 基準高さオフセット
	static constexpr float EFFECT_SCALE = 4.5f;      // 表示スケール
	static constexpr float EFFCT_PLAYSPEED = 0.20f;  // 再生速度
	static constexpr float EFFECT_ENDTIME = 120.0f;  // 終了許容閾値

	int   effect_handle;         // 一時ハンドル
	int   effect_playinghandle;  // 再生中ハンドル
	float effect_playtime;       // 再生時間
	bool  effect_isplay;         // 再生中
	bool  effect_isend;          // 終了済

	bool  effect_initialized = false; // 初期化済みか
	int   effect_handles[EFFECT_NUM]{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1, -1,-1 }; // 読み込み済配列

	// ループ再生管理
	bool   loop_enabled[EFFECT_NUM]{ false };
	int    loop_playing_handles[EFFECT_NUM]{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1 };
	VECTOR loop_positions[EFFECT_NUM]{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1 }; // 最終位置
};
