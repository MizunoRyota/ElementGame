#pragma once
#include "Dxlib.h"
#include <string>

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Initialize() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract; 

	virtual const int& GetDamageStrength() const { return obj_damagestrength; }
	virtual const int& GetHp() const { return obj_hp; }
	virtual const int& GetHandle() const { return obj_modelhandle; }
	virtual const VECTOR& GetPosition() const { return obj_position; }
	virtual const VECTOR& GetDirection() const { return obj_direction; }

	std::string GetNameTag() const { return obj_name; }

	virtual void Setposition(const VECTOR set) { obj_position = set; }

protected:
	std::string obj_name = "null";
	VECTOR obj_position =VGet(0,0,0);
	VECTOR obj_direction = VGet(0,0,0);
	int obj_modelhandle = 0;
	int obj_effecthandle = 0;
	int obj_hp = 0;
	int obj_damagestrength = 0;
	float obj_modelscale = 0;
};