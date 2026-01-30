#pragma once

class PlayerJump
{
public:
	PlayerJump(VECTOR& pos);
	~PlayerJump();

	void Update();

private:
	static constexpr float GROUND_POS_Y = 0.0f;

	static constexpr float JUMP_VELOCITY = 0.35f;
	static constexpr float JUMP_GRAVITY = 0.02f;
	static constexpr float JUMP_MAX_FALL_SPEED = 0.75f;

	VECTOR& player_position;

	float jump_velocity_y;
	bool player_is_grounded;
};