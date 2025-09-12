#include "stdafx.hpp"
#include "CharacterBase.hpp"

bool CharacterBase::TakeDamage(int amount)
{
	if (amount <= 0) return false;
	if (IsDead()) return false;
	if (IsInvincible()) return false;

	obj_hp -= amount;
	if (obj_hp < 0) obj_hp = 0;
	damage_invincible_timer_ = damage_invincible_duration;
	return true;
}

void CharacterBase::TickDamageCooldown()
{
	if (damage_invincible_timer_ > 0)
	{
		--damage_invincible_timer_;
	}
}