#pragma once
#include "../EnemyStateBase.hpp"

// EnemyStateFloat:
// 特殊行動の前段として、敵をステージ中央（原点付近）へ移動させるステート。
// - 原点に到達したら `STATE_SPECIAL_CHARGE` へ遷移
// - 到達までは一定速度で原点へ向かって移動
class EnemyStateFloat : public EnemyStateBase
{
public:
	EnemyStateFloat(VECTOR& position);
	~EnemyStateFloat();

	void Enter() override;
	void Update() override;
	void Exit() override {};

	EnemyStateKind GetNextState() override;

private:
	static constexpr float MOVE_SPEED    = 0.125f; // 原点へ戻る速度
	static constexpr float ORIGIN_OFFSET = 0.1f;   // 原点到達判定の許容誤差

	VECTOR& enemy_position;
	bool position_is_origin; // 原点に到達したか
};
