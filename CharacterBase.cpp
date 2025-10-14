#include "stdafx.hpp"
#include "CharacterBase.hpp"

bool CharacterBase::TakeDamage(int amount)
{
	if (amount <= 0) return false;
	if (IsDead()) return false;
	if (IsInvincible()) return false;

	obj_hp -= amount;
	if (obj_hp < 0) obj_hp = 0;
	//damage_invincible_timer_ = damage_invincible_duration;
	return true;
}

void CharacterBase::TickDamageCooldown()
{
	if (damage_invincible_timer_ > 0)
	{
		--damage_invincible_timer_;
	}
}

void CharacterBase::CheckMoveRange()
{
	////中心からプレイヤーの距離を測る
	float r = VSize(VSub(obj_position, VGet(0.0f, 0.0f, 0.0f)));

	////一定の距離に達したらそれ以上いけないようにする

	if (r > ReturnRange || r < -ReturnRange)
	{

		//中心座標からプレイヤー座標の距離

		VECTOR distance = VSub(VGet(0.0f, 0.0f, 0.0f), obj_position);

		//正規化

		distance = VNorm(distance);

		//戻す量を計算、加算する

		VECTOR returnPosition = VScale(distance, (r - ReturnRange));

		obj_position = VAdd(obj_position, returnPosition);
	}
}