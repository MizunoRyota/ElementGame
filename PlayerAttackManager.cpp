#include "Dxlib.h"
#include "PlayerAttackManager.hpp"
#include "PlayerFireAttack.hpp"
#include "PlayerWindAttack.hpp"
#include "PlayerWaterAttack.hpp"
PlayerAttackManager::PlayerAttackManager(int modelhandle)
	: MouseWheelRot(0)
	, model_handle(0)
	, isWind(false)
	, isFire(true)
	, isWater(false)
{
	this->model_handle = modelhandle;
	fire_attack = std::make_shared<PlayerFireAttack>(model_handle);
	wind_attack = std::make_shared<PlayerWindAttack>(model_handle);
	water_attack = std::make_shared<PlayerWaterAttack>(model_handle);
}
PlayerAttackManager::~PlayerAttackManager()
{
}

void PlayerAttackManager::Update(const Input& input, const Camera& camera)
{
	ChangeAttack();
	UpdateAttack(input, camera);
}

void PlayerAttackManager::ChangeAttack()
{
	// ‘O‰ñ GetMouseWheelRotVol ‚ªŒÄ‚Î‚ê‚Ä‚©‚ç¡‰ñ‚Ü‚Å‚Ì‰ñ“]—Ê‚ð‘«‚·
	MouseWheelRot += GetMouseWheelRotVol();

	if (MouseWheelRot > 0)
	{
		if (isWind)
		{
			isWind = false;
			isFire = true;
		}
		else if (isFire)
		{
			isFire = false;
			isWater = true;

		}
		else if (isWater)
		{
			isWater = false;
			isWind = true;
		}
	}

	else if (MouseWheelRot < 0)
	{
		if (isWind)
		{
			isWind = false;
			isWater = true;

		}
		else if (isFire)
		{
			isFire = false;
			isWind = true;

		}
		else if (isWater)
		{
			isWater = false;
			isFire = true;

		}
	}

	MouseWheelRot = 0;
}

void PlayerAttackManager::UpdateAttack(const Input& input, const Camera& camera)
{
	if (isFire)
	{
		water_attack->Initialize();
		wind_attack->Initialize();
		fire_attack->Update(input,camera);
	}
	else if (isWater)
	{
		wind_attack->Initialize();
		fire_attack->Initialize();

		water_attack->Update(input, camera);
	}
	else if (isWind)
	{
		fire_attack->Initialize();
		water_attack->Initialize();
		wind_attack->Update(input, camera);
	}
}