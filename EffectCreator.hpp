#pragma once
#include "stdafx.hpp"

// Effekseer を用いた 3D エフェクト管理クラス（簡易）
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
	};

	static EffectCreator& GetEffectCreator()
	{
		static EffectCreator instance; // シングルトン生成
		return instance;
	}

	void Initialize();   // 初期化（エフェクト読み込み）
	void Update();       // フレーム更新（Effekseer更新）
	void Draw();         // 描画呼び出し
	void Play(EffectType EffectType, const VECTOR& position); // 再生（戻り不要）
	int  PlayReturn(EffectType EffectType, const VECTOR& position); // 再生ハンドル返却

	// ループ再生開始（StopLoop を呼ぶまで継続再生）
	void PlayLoop(EffectType type, const VECTOR& position);
	// ループ再生停止
	void StopLoop(EffectType type);
	// ループ再生中エフェクトの位置更新
	void SetLoopPosition(EffectType type, const VECTOR& position);

	void SetRotateEffect(EffectType type, const VECTOR& dir);

private:
	EffectCreator() = default;
	~EffectCreator() = default;
	EffectCreator(const EffectCreator&) = delete;
	EffectCreator& operator=(const EffectCreator&) = delete;

	static constexpr int EFFECT_NUM = 14;          // 読み込む最大エフェクト数
	static constexpr float EFFECT_HIGHT = 0.3f;   // 再生基準高さオフセット
	static constexpr float EFFECT_SCALE = 4.5f;   // 共通スケール(未使用)
	static constexpr float EFFCT_PLAYSPEED = 0.20f; // 再生時間増加量
	static constexpr float EFFECT_ENDTIME = 120.0f; // 終了判定閾値

	int   effect_handle;         // 読み込み用一時ハンドル
	int   effect_playinghandle;  // 現在再生中ハンドル
	float effect_playtime;       // 累積再生時間
	bool  effect_isplay;         // 再生中フラグ
	bool  effect_isend;          // 再生完了フラグ

	bool effect_initialized = false;      // 初期化済み
	int  effect_handles[EFFECT_NUM]{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // 読み込み済みハンドル群

	// ループ再生管理
	bool   loop_enabled[EFFECT_NUM]{ false };
	int    loop_playing_handles[EFFECT_NUM]{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	VECTOR loop_positions[EFFECT_NUM]{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // 最後に設定された位置
};
