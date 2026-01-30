#pragma once
#include "../EnemyStateBase.hpp"
#include "../EffectCreator.hpp" // エフェクト生成

class EnemyStateChase : public EnemyStateBase
{
public:
	EnemyStateChase(VECTOR& position);
	~EnemyStateChase();

	void Enter() override;

	void Update() override;

	void Exit() override ;

	bool RangeWithin(); // 追跡レンジ内か
	void ChoseRange();

	EnemyStateKind GetNextState()override;

private:
	EffectCreator::EffectType MapEffectTypeForAttack(float attackState) const; // 攻撃ステートに応じたエフェクト種別へ変換

	static constexpr float FIRE_RANGE = 5.0f;
	static constexpr float WATER_RANGE = 11.0f;
	static constexpr float WIND_RANGE = 12.0f;
	static constexpr float JUMPATTACK_RANGE = 30.0f;

	static constexpr float SPECIAL_RANGE = 8.0f;
	static constexpr float MOVE_SPEED = 0.175f;   // 基本移動速度
	static constexpr float ORIGIN_OFFSET = 0.1f;  // 原点とみなす誤差
	VECTOR& chase_position;
	float chase_range; // 追跡開始距離
	int enemy_hand_effect_handle;
	float range_squared;

};

