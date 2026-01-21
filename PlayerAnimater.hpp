#pragma once
#include "PlayerStateKind.hpp"
#include "AnimaterBase.hpp"

class PlayerAnimater : public AnimaterBase
{
public:
	PlayerAnimater(int modelhandle, PlayerStateKind& playerState);
	virtual~PlayerAnimater();

	void InitializeAnimationData()override; // データ登録

	void Update()override;            // 状態更新
	void SwitchAnimation()override;   // ステート遷移判定

protected:
	PlayerStateKind& player_state; // 参照: プレイヤーステート

private:
	static constexpr float DEFAULT_ANIMATION_SPEED = 0.5f;
};