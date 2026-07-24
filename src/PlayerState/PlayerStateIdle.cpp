#include "PlayerStateIdle.hpp"
#include "../ObjectAccessor.hpp"
#include "../EffectCreator.hpp"
PlayerStateIdle::PlayerStateIdle()
{

}

PlayerStateIdle::~PlayerStateIdle()
{
}

void PlayerStateIdle::Update()
{
	if (ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak())
	{
		ObjectAccessor::GetObjectAccessor().ChangeIsReadyLaser(true);
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::ChargeLaser, ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());
	}

	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::ChargeLaser, ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());

}

void PlayerStateIdle::Exit()
{
	if (!ObjectAccessor::GetObjectAccessor().GetIsReadyLaser())
	{
		EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeLaser);
	}
}

PlayerStateKind PlayerStateIdle::GetNextState()
{
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && ObjectAccessor::GetObjectAccessor().GetIsReadyLaser() && ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() != PlayerStateKind::STATE_ATTACK
		|| ObjectAccessor::GetObjectAccessor().GetIsInputBottunY() && ObjectAccessor::GetObjectAccessor().GetIsReadyLaser() && ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() != PlayerStateKind::STATE_ATTACK
		|| ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() == PlayerStateKind::STATE_LASER
		|| ObjectAccessor::GetObjectAccessor().GetIsInputBottunY() && ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger() && ObjectAccessor::GetObjectAccessor().GetIsReadyLaser())
	{
		ObjectAccessor::GetObjectAccessor().ChangeIsReadyLaser(false);
		return PlayerStateKind::STATE_LASER;
	}
	if (ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger() || (GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		return PlayerStateKind::STATE_ATTACK;
	}
	else
	{
		return PlayerStateKind::STATE_IDLE;
	}
}