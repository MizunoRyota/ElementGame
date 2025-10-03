#include "stdafx.hpp"
#include "SpecialAttack.hpp"

SpecialAttack::SpecialAttack()
	:specialattack_ischarge(false)   // チャージ中フラグ
	,specialattack_isactive(false)   // 発動中フラグ
	,specialattack_isend(false)      // 終了フラグ
{
}

SpecialAttack::~SpecialAttack() {}

