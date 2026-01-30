#include "stdafx.hpp"
#include "PlayerJump.hpp"
#include "ObjectAccessor.hpp"
PlayerJump::PlayerJump(VECTOR& pos)
	:player_position(pos)
	,jump_velocity_y(0.0f)
	,player_is_grounded(true)
{
}

PlayerJump::~PlayerJump()
{
}

void PlayerJump::Update()
{
	if (player_position.y <= GROUND_POS_Y)
	{
		player_position.y = GROUND_POS_Y;
		jump_velocity_y = 0.0f;
		player_is_grounded = true;
	}
	else
	{
		player_is_grounded = false;
	}

	const bool jump_input = ObjectAccessor::GetObjectAccessor().GetIsInputBottunA() || (CheckHitKey(KEY_INPUT_SPACE) != 0);

	if (player_is_grounded && jump_input)
	{
		jump_velocity_y = JUMP_VELOCITY;
		player_is_grounded = false;
	}

	if (!player_is_grounded)
	{
		jump_velocity_y -= JUMP_GRAVITY;
		if (jump_velocity_y < -JUMP_MAX_FALL_SPEED)
		{
			jump_velocity_y = -JUMP_MAX_FALL_SPEED;
		}

		player_position.y += jump_velocity_y;
	}
}