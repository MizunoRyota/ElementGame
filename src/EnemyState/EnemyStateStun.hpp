#pragma once

#include "../EnemyStateBase.hpp"
class EnemyStateStun : public EnemyStateBase
{
	public:
	EnemyStateStun();
	~EnemyStateStun();
	void Enter()override;
	void Update()override;
	void Exit()override;
	EnemyStateKind GetNextState()override;
private:
	static constexpr float STUN_TIME = 2000.0f;               // 発射位置オフセット(Y方向・モデル調整)
	static constexpr float STUN_HEIGHT = 2.5f;               // 発射位置オフセット(Y方向・モデル調整)

	static constexpr float STUN_DECREASE_TIME = 10.0f;               // 発射位置オフセット(Y方向・モデル調整)
	float stun_time;
};