#pragma once
#include <unordered_map>
#include "PlayerState.hpp"
#include "AnimaterBase.hpp"
class PlayerAnimater : public AnimaterBase
{
public:
	PlayerAnimater(int modelhandle, PlayerState& enemystate);
	virtual~PlayerAnimater();

	enum class AnimKind : int
	{
		Idle = 9,
		Attack =7,
	};

	void InitializeAnimationData()override;

	void Update()override;
	void SwitchAnimation()override;

protected:
	PlayerState& player_state;
};