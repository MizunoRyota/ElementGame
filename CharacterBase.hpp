#pragma once
#include "GameObject.hpp"

class CharacterBase : public GameObject
{
public:
	CharacterBase() = default;
	virtual ~CharacterBase() = default;

	virtual void UpdateStateAction() abstract; // 各派生で行動ステート更新

	// シーン別描画（共通で通常Drawを呼ぶデフォルト実装）
	void DrawTitle() override { Draw(); }
	void DrawGameOver() override { Draw(); }
	void DrawGameClear() override { Draw(); }

	// === Damage System API ===
	// ダメージ適用。HPを減少させた場合 true を返す
	bool TakeDamage(int amount);

	// 無敵時間(フレーム)設定
	void ConfigureDamageCooldown(int frames) { damage_invincible_duration = frames; }

	// 無敵タイマー進行(Update 等で呼ぶ)
	void TickDamageCooldown();

	void CheckMoveRange(); // 行動範囲外チェック＆補正

	bool IsInvincible() const { return damage_invincible_timer_ > 0; } // 現在無敵か
	bool IsDead() const { return obj_hp <= 0; } // HP が 0 以下か
	float GetCapsuleRadius() const { return COLLISION_CAPSULE_RADIUS; } // 衝突半径
	float GetCapsuleHeight() const { return COLLISION_CAPSULE_HEIGHT; } // 衝突高さ
protected:
	static constexpr float ReturnRange = 20.0f; // 自動復帰させる境界半径
	float COLLISION_CAPSULE_RADIUS = 0;
	float COLLISION_CAPSULE_HEIGHT = 0;
	int   character_handname = 0;              // モデル内「手」ボーンのフレームID
	VECTOR character_handposition = VGet(0, 0, 0); // 発射等に用いる手先位置キャッシュ

	// === Damage System State ===
	int damage_invincible_timer_ = 0;          // 残り無敵フレーム（0 で通常）
	int damage_invincible_duration = 0;        // 被弾後に付与する無敵総フレーム
};