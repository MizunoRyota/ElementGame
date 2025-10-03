#pragma once
#include <unordered_map>
#include "PlayerState.hpp"
#include "AnimaterBase.hpp"
class PlayerAnimater : public AnimaterBase
{
public:
	PlayerAnimater(int modelhandle, PlayerState& enemystate);
	virtual~PlayerAnimater();

	// プレイヤー用アニメーション種別
	enum class AnimKind : int
	{
		Idle = 9,
		Attack = 7,
	};

	void InitializeAnimationData()override; // データ登録

	void Update()override;            // 状態更新
	void SwitchAnimation()override;   // ステート遷移判定

protected:
	PlayerState& player_state; // 参照: プレイヤーステート
};