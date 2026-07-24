#include "stdafx.hpp"
#include "PlayerAttack.hpp"
#include "BulletFire.hpp"
#include "../PlayerStateKind.hpp"
#include "../EffectCreator.hpp"
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

	if (ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak())
	{
		ObjectAccessor::GetObjectAccessor().ChangeIsReadyLaser(true);
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::ChargeLaser, ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) || (ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger()))
	{
		// 手先位置 + 視線方向へオフセットして弾を発射
		player_bullet->FirePlayer(VAdd(ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition(), VScale(ObjectAccessor::GetObjectAccessor().GetCameraDirection(), BULLETFIRE_DISTANCE)), ObjectAccessor::GetObjectAccessor().GetCameraDirection(), BULLET_SPEED);
	}

	player_bullet->FireUpdate();

}

void PlayerAttack::Exit()
{
	if (!ObjectAccessor::GetObjectAccessor().GetIsReadyLaser())
	{
		EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeLaser);
	}
}

PlayerStateKind PlayerAttack::GetNextState()
{
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && ObjectAccessor::GetObjectAccessor().GetIsReadyLaser() && ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() != PlayerStateKind::STATE_ATTACK
		|| ObjectAccessor::GetObjectAccessor().GetIsInputBottunY() && ObjectAccessor::GetObjectAccessor().GetIsReadyLaser() && ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() != PlayerStateKind::STATE_ATTACK
		|| ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() == PlayerStateKind::STATE_LASER
		|| ObjectAccessor::GetObjectAccessor().GetIsInputBottunY() && ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger() && ObjectAccessor::GetObjectAccessor().GetIsReadyLaser())
	{
		ObjectAccessor::GetObjectAccessor().ChangeIsReadyLaser(false);
		return  PlayerStateKind::STATE_LASER;
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) || (ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger()))
	{
		return  PlayerStateKind::STATE_ATTACK;
	}
	else
	{
        return PlayerStateKind::STATE_IDLE;
	}
}