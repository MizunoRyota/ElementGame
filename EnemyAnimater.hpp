#pragma once
#include <unordered_map>
#include "EnemyState.hpp"
#include "AnimaterBase.hpp"
class EnemyAnimater : public AnimaterBase
{
public:
	EnemyAnimater(int modelhandle,  EnemyState& enemystate);
	virtual~EnemyAnimater();

	enum class AnimKind : int
	{
		OnDamage = 0,
		Walkback = 1,
		Die = 2,
		GroundAttack = 3,
		Float = 4,
		SpecialAttack = 5,
		RunLeft = 6,
		Charge = 7,
		RunRight = 8,
		WindAttack = 9,
		WaterAttack = 10,
		FireAttack = 11,
		JumpAttack = 12,
		Idle = 13,
		Chase = 14,
	};
	void InitializeAnimationData()override;

	void Update()override;
	void SwitchAnimation()override;

protected:
	EnemyState& enemy_state;
};