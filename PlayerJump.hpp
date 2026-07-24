#pragma once

class PlayerJump
{
public:
	PlayerJump(VECTOR& pos);
	~PlayerJump();

	void Update();

private:
	static constexpr float GROUND_POS_Y = 0.0f; // 地面のポジション
	static constexpr float JUMP_VELOCITY = 0.35f; // ジャンプの向き
	static constexpr float JUMP_GRAVITY = 0.02f; // 重力
	static constexpr float JUMP_MAX_FALL_SPEED = 0.75f; // 落ちる最大速度

	VECTOR& player_position; // プレイヤーのポジション

	float jump_velocity_y; //ジャンプの向き
	bool player_is_grounded; //プレイヤーが地面にいるか
};