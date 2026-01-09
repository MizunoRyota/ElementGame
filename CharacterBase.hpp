#pragma once
#include "GameObject.hpp"

// キャラクター共通基底。ダメージ・無敵・当たり判定サイズなどの共通処理を持つ
class CharacterBase : public GameObject
{
public:
	CharacterBase() = default;
	virtual ~CharacterBase() = default;

	virtual void InitializeStates()abstract;

	virtual void UpdateStateAction() abstract; // 各派生で行動ステート更新

	virtual void UpdateHandEffect() abstract;

	// シーン別描画（共通で通常Drawを呼ぶデフォルト実装）
	void DrawTitle() override { Draw(); }
	void DrawGameOver() override { Draw(); }
	void DrawGameClear() override { Draw(); }

	// === Damage System API ===
	void ConfigureDamageCooldown(int frames) { damage_invincible_duration = frames; } // 無敵時間(フレーム)設定
	bool TakeDamage(int amount);                    // ダメージ適用。HPを減少させた場合 true
	void TickDamageCooldown();                      // 無敵タイマー進行(Update 等で呼ぶ)

	void CheckMoveRange();                          // 行動範囲外チェック＆補正

	bool IsInvincible()			const { return damage_invincible_timer > 0; }		// 現在無敵か
	bool IsDead()				const { return obj_hp <= 0; }						// HP が 0 以下か
	float GetCapsuleRadius()	const { return COLLISION_CAPSULE_RADIUS; }			// 衝突半径
	float GetCapsuleHeight()	const { return COLLISION_CAPSULE_HEIGHT; }			// 衝突高さ
	virtual const int& GetHp()	const { return obj_hp; }							// 現在HP
	VECTOR GetHandPosition()	const { return character_hand_position; }			//キャラクターの手のポジション

protected:
	static constexpr float MAX_RANGE = 20.0f;			// 自動復帰させる境界半径
	static constexpr float TAKEDAMAGE_COOLDOWN = 5.0f;  // 被弾無敵(フレーム)

	float COLLISION_CAPSULE_RADIUS = 0;					// 当たり判定(半径)
	float COLLISION_CAPSULE_HEIGHT = 0;					// 当たり判定(高さ)

	int character_handname = 0;							// モデル内「手」ボーンのフレームID

	VECTOR character_hand_position = VGet(0, 0, 0);		// 発射等に用いる手先位置キャッシュ

	// === Damage System State ===
	int damage_invincible_timer = 0;					// 残り無敵フレーム（0 で通常）
	int damage_invincible_duration = 0;					// 被弾後に付与する無敵総フレーム
};