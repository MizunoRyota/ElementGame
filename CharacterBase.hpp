#include "DxLib.h"
#include "GameObject.hpp"
#pragma once

class CharacterBase : public GameObject
{
public:
	CharacterBase() = default;
	virtual ~CharacterBase() = default;

	virtual void UpdateStateAction() abstract;

protected:

	int character_handname = 0;

	VECTOR character_handposition = VGet(0, 0, 0);

};
