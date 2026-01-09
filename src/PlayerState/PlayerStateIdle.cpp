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
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::ChargeLaser, ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());
	}
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::ChargeLaser, ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());

}

void PlayerStateIdle::Exit()
{
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeLaser);
}

PlayerStateKind PlayerStateIdle::GetNextState()
{
	if (ObjectAccessor::GetObjectAccessor().GetIsInputRightTrigger() || (GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		return PlayerStateKind::STATE_ATTACK;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak()
		|| ObjectAccessor::GetObjectAccessor().GetIsInputBottunY() && ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak()
		|| ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() == PlayerStateKind::STATE_LASER)
	{
		return PlayerStateKind::STATE_LASER;
	}
	else
	{
		return PlayerStateKind::STATE_IDLE;
	}
}