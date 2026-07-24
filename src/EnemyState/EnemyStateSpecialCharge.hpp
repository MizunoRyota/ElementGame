#pragma once
#include "../EnemyStateBase.hpp"

class EnemyStateBase;

// EnemyStateSpecialCharge:
// 特殊攻撃のチャージ（溜め）ステート。
// - チャージ時間が尽きたら `STATE_SPECIALATTACK` へ
// - チャージ中にクリスタルが破壊されたら `STATE_STUN` へ（キャンセル/弱点ギミック）
// - バリア/チャージのループ演出を再生し続ける
class EnemyStateSpecialCharge : public EnemyStateBase
{
public:
	EnemyStateSpecialCharge();
	~EnemyStateSpecialCharge();

	void Enter()override;
	void Update()override;
	void Exit()override;

	EnemyStateKind GetNextState()override;

private:
	static constexpr float SPECIALATTACK_CHARGE_TIME = 2000.0f;			// チャージ総時間（疑似時間）
	static constexpr float SPECIALATTACK_CHARGE_DECREACENUM = 3.75f;	// 1更新あたりの減算量

	float specialattack_charge_time; // 残りチャージ時間
};
