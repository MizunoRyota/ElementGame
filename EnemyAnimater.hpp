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
		WalkBack = 0,
		Die = 1,
		GroundAttack = 2,
		Float = 3,
		SpecialAttack = 4,
		RunLeft = 5,
		Charge = 6,
		RunRight = 7,
		FireAttack = 8,
		WaterAttack = 9,
		WindAttack = 10,
		JumpAttack = 11,
		Idle = 12,
		Chase = 13,
		OnDamage = 14,
	};
	void InitializeAnimationData()override; // モーションデータ登録

	void Update()override; // 状態更新
	void SwitchAnimation()override; // ステートに応じた遷移

protected:
	EnemyState& enemy_state; // 参照: エネミー行動ステート
};