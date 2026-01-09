#pragma once
#include "../EnemyStateBase.hpp"

class EnemyStateFloat : public EnemyStateBase
{
public:
	EnemyStateFloat(VECTOR& position);
	~EnemyStateFloat();
	void Enter() override ;

	void Update() override ;

	void Exit() override {};
	EnemyStateKind GetNextState()override;

private:
	static constexpr float MOVE_SPEED = 0.125f;   // 基本移動速度
	static constexpr float ORIGIN_OFFSET = 0.1f;  // 原点とみなす誤差
	VECTOR& enemy_position;
	bool position_is_origin; // 現在原点にいるか

};
