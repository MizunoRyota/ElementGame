#include "stdafx.hpp"
#include "SpecialAttack.hpp"

SpecialAttack::SpecialAttack()
	:specialattack_ischarge(false)   // チャージ中フラグ
	,specialattack_isactive(false)   // 発動中フラグ
	,specialattack_isend(false)      // 終了フラグ
{


}

SpecialAttack::~SpecialAttack() {}

void SpecialAttack::Initialize()
{
	specialattack_ischarge = true;   // チャージ中フラグ

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
		specialattack_ischarge = false;   // チャージ中フラグ
	}
}