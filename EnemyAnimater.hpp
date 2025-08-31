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
		Chase = 0,
		OnDamage = 1,
		Walkback = 2,
		Die = 3,
		GroundAttack = 4,
		RunLeft = 5,
		Charge = 6,
		RunRight = 7,
		WindAttack = 8,
		WaterAttack = 9,
		FireAttack = 10,
		JumpAttack = 11,
		Idle = 12,
	};
	void InitializeAnimationData()override;

	void Update()override;
	void SwitchAnimation()override;

protected:
	EnemyState& enemy_state;
};