#include "PlayerStateIdle.hpp"
#include "../ObjectAccessor.hpp"
#include "../EffectCreator.hpp"
PlayerStateIdle::PlayerStateIdle()
{
	laser_is_ready = false;
}

PlayerStateIdle::~PlayerStateIdle()
{
}

void PlayerStateIdle::Update()
{
	if (ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak())
	{
		laser_is_ready = true;
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::ChargeLaser, ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());
	}

	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::ChargeLaser, ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());

}

void PlayerStateIdle::Exit()
{
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeLaser);
	laser_is_ready = false;
}

PlayerStateKind PlayerStateIdle::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger() || (GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		return PlayerStateKind::STATE_ATTACK;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && laser_is_ready
		|| ObjectAccessor::GetObjectAccessor().GetIsInputBottunY() && laser_is_ready
		|| ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() == PlayerStateKind::STATE_LASER)
	{
		return PlayerStateKind::STATE_LASER;
	}
	else
	{
		return PlayerStateKind::STATE_IDLE;
	}
}