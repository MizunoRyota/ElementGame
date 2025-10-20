#pragma once
#include "stdafx.hpp"

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Initialize() abstract;
	virtual void Update() abstract;

	virtual void DrawTitle() abstract;
	virtual void Draw() abstract; 
	virtual void DrawGameOver() abstract;
	virtual void DrawGameClear() abstract;

	// 追加: シーン別更新処理（必要なクラスでオーバーライド）
	virtual void UpdateGameClear() abstract;
	virtual void UpdateGameOver() abstract;
	virtual void UpdateTitle() abstract;

	virtual const int& GetDamageStrength() const { return obj_damagestrength; }
	virtual const int& GetHp() const { return obj_hp; }
	virtual const int& GetHandle() const { return obj_modelhandle; }
	virtual const VECTOR& GetPosition() const { return obj_position; }
	virtual const VECTOR& GetDirection() const { return obj_direction; }
	virtual VECTOR GetTarget() const { return VAdd(obj_position, VGet(0, TARGETHIGHT, 0)); }
	std::string GetNameTag() const { return obj_name; }

	virtual const std::shared_ptr<GameObject> SetGameObject(const std::shared_ptr<GameObject>& set_object) { return set_object; }

	virtual void Setposition(const VECTOR set) { obj_position = set; }

protected:
	static constexpr float TARGETHIGHT = 2.25f;

	std::string obj_name = "null";
	VECTOR obj_position =VGet(0,0,0);
	VECTOR obj_direction = VGet(0,0,0);
	int obj_modelhandle = 0;
	int obj_effecthandle = 0;
	int obj_hp = 0;
	int obj_damagestrength = 0;
	float obj_modelscale = 0;
};