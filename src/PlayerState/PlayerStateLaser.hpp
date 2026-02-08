#pragma once

#include "../PlayerStateBase.hpp"

class PlayerStateLaser : public PlayerStateBase
{
public:
	PlayerStateLaser();
	~PlayerStateLaser();

	void Enter()override;

	void Update()override;

	bool FireEnd();

	void Exit()override;

	PlayerStateKind GetNextState()override;

private:

	static constexpr float LASER_DISTANCE = 2.0f; // 発射位置: 視線カメラからのオフセット  
	static constexpr float LASER_MAX_TIME = 2000.0f;  // 発射クール時間
	static constexpr float LASER_MAX_LENGTH = 30.0f;  // レーザーの距離
	static constexpr float LASER_DECREACE_TIME = 10.0f;  // 発射クール時間
	static constexpr int JOYPAD_VIBERATON_POWER = 750; // パッドの振動の強さ

	float laser_timer;
	bool laser_is_ready;
	bool laser_is_fire;

};
