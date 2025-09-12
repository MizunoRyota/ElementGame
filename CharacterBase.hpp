#include "GameObject.hpp"
#pragma once

class CharacterBase : public GameObject
{
public:
	CharacterBase() = default;
	virtual ~CharacterBase() = default;

	virtual void UpdateStateAction() abstract;

	// === Damage System API ===
	// ダメージ適用。実際に HP を減らした場合 true。
	bool TakeDamage(int amount);

	// 無敵時間(フレーム)設定。
	void ConfigureDamageCooldown(int frames) { damage_invincible_duration = frames; }

	// 毎フレーム呼ぶ（Update 内など）。無敵タイマー減算。
	void TickDamageCooldown();

	bool IsInvincible() const { return damage_invincible_timer_ > 0; }
	bool IsDead() const { return obj_hp <= 0; }

protected:
	int character_handname = 0;
	VECTOR character_handposition = VGet(0, 0, 0);

	// === Damage System State ===
	int damage_invincible_timer_ = 0;
	int damage_invincible_duration = 0;
};
