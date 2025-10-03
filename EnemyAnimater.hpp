#pragma once
#include <unordered_map>
#include "EnemyState.hpp"
#include "AnimaterBase.hpp"
class EnemyAnimater : public AnimaterBase
{
public:
	EnemyAnimater(int modelhandle,  EnemyState& enemystate);
	virtual~EnemyAnimater();

	// エネミー用アニメーション種別
	enum class AnimKind : int
	{
		OnDamage = 0,
		Walkback = 1,
		Die = 2,
		GroundAttack = 3,
		Float = 4,
		SpecialAttack = 5,
		RunLeft = 6,
		Charge = 7,
		RunRight = 8,
		FireAttack = 9,
		WaterAttack = 10,
		WindAttack = 11,
		JumpAttack = 12,
		Idle = 13,
		Chase = 14,
	};
	void InitializeAnimationData()override; // モーションデータ登録

	void Update()override; // 状態更新
	void SwitchAnimation()override; // ステートに応じた遷移

protected:
	EnemyState& enemy_state; // 参照: エネミー行動ステート
};