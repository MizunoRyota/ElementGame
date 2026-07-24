#pragma once
#include "../EnemyStateBase.hpp"
#include "../EffectCreator.hpp" // エフェクト種別

// EnemyStateChase:
// 選択済みの攻撃に入るため、プレイヤーへ接近するステート。
// - 事前に `enemy_attack_state`（EnemyStateBase 側で保持）が決定済みである前提
// - 攻撃種別に応じて「射程」(`chase_range`) を設定し、射程内に入ったら攻撃ステートへ遷移
// - 追跡中は手元に攻撃準備のエフェクト（弾種に応じた見た目）を出す
class EnemyStateChase : public EnemyStateBase
{
public:
	EnemyStateChase(VECTOR& position);
	~EnemyStateChase();

	void Enter() override;

	void Update() override;

	void Exit() override ;

	// プレイヤーが射程内に入ったか（距離判定）
	bool RangeWithin();

	// 攻撃状態から追跡終了距離（射程）を決める
	void ChoseRange();

	// 状態遷移（射程内→攻撃、射程外→被弾割り込みなど）
	EnemyStateKind GetNextState() override;

private:
	// 攻撃種別（レンジ）に対応するエフェクト種別へ変換
	EffectCreator::EffectType MapEffectTypeForAttack(float attackState) const;

	// 各攻撃の「射程」（この距離以内に入ったら追跡を止めて攻撃へ）
	static constexpr float FIRE_RANGE = 5.0f;
	static constexpr float WATER_RANGE = 11.0f;
	static constexpr float WIND_RANGE = 12.0f;
	static constexpr float JUMPATTACK_RANGE = 30.0f;
	static constexpr float SPECIAL_RANGE = 8.0f;

	static constexpr float MOVE_SPEED = 0.175f; // 追跡移動速度
	static constexpr float ORIGIN_OFFSET = 0.1f;   // 0判定の許容誤差（将来拡張用）

	VECTOR& chase_position; // 敵の位置参照（外部の位置を直接更新する）

	float chase_range; // 射程（距離しきい値）
	int enemy_hand_effect_handle; // 手元エフェクトハンドル（EnemyStateBase の仕組みと併用）
	float range_squared; // 距離比較用（最適化目的の二乗値）
};

