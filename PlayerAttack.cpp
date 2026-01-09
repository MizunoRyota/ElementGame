#include "stdafx.hpp"
#include "PlayerAttack.hpp"
#include "BulletFire.hpp"
#include "../PlayerStateKind.hpp"
#include "ObjectAccessor.hpp"

PlayerAttack::PlayerAttack()
{
	player_bullet = std::make_shared<BulletFire>();
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Enter()
{
}

void PlayerAttack::Update()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) || (ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger()))
	{
		// 手先位置 + 視線方向へオフセットして弾を発射
		player_bullet->FirePlayer(VAdd(ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition(), VScale(ObjectAccessor::GetObjectAccessor().GetCameraDirection(), BULLETFIRE_DISTANCE)), ObjectAccessor::GetObjectAccessor().GetCameraDirection(), BULLET_SPEED);
	}

	player_bullet->FireUpdate();

}

void PlayerAttack::Exit()
{

}

PlayerStateKind PlayerAttack::GetNextState()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) || (ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger()))
	{
		return  PlayerStateKind::STATE_ATTACK;
	}
	else
	{
        return PlayerStateKind::STATE_IDLE;
	}
}