#pragma once
#include <memory>
#include <vector>
#include "PlayerAttackBase.hpp"


class Input;

class PlayerAttackManager
{
public:
	PlayerAttackManager(int modelhandle);
	~PlayerAttackManager();

	void Update(const Input& input, const Camera& camera);
	void ChangeAttack();
	void UpdateAttack(const Input& input, const Camera& camera);
private:
	std::shared_ptr<PlayerAttackBase> fire_attack;
	std::shared_ptr<PlayerAttackBase> wind_attack;
	std::shared_ptr<PlayerAttackBase> water_attack;
	bool isFire;
	bool isWind;
	bool isWater;
	int model_handle;
	int MouseWheelRot;
};
