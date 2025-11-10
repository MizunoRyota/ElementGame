#include "stdafx.hpp"
#include "SpecialAttack.hpp"

SpecialAttack::SpecialAttack()
	:specialattack_is_charge(false)   // チャージ中フラグ
	,specialattack_is_active(false)   // 発動中フラグ
	,specialattack_is_end(false)      // 終了フラグ
{
	specialattack_charge_time = 0;

}

SpecialAttack::~SpecialAttack() {}

void SpecialAttack::Initialize()
{
	specialattack_is_charge = true;   // チャージ中フラグ

	specialattack_charge_time = SPECIALATTACK_CHARGE_TIME;
}

void SpecialAttack::UpdateChrgeCount()
{
	specialattack_charge_time -= SPECIALATTACK_CHARGE_DECREACENUM;
	ChangeIsChargeFlag();
}

void SpecialAttack::ChangeIsChargeFlag()
{
	if (specialattack_charge_time <= 0)
	{
		specialattack_is_charge = false;   // チャージ中フラグ
	}
}