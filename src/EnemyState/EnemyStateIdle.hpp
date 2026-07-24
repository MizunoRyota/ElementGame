#pragma once
#include "../EnemyStateBase.hpp"

// EnemyStateIdle:
// 敵の待機ステート。
// - 基本的に何もしない（アニメ再生のみ）
// - 現状は常に `STATE_IDLE` を返す実装
class EnemyStateIdle : public EnemyStateBase
{
public:
	EnemyStateIdle();
	~EnemyStateIdle();


	void Enter() override {};

	void Update() override {};

	void Exit() override {};

	EnemyStateKind GetNextState()override ;

private:

};
