#include "PlayerStateLaser.hpp"
#include "../../EffectCreator.hpp"
#include "../ObjectAccessor.hpp"
#include "../PlayerStateKind.hpp"
#include "../src/Sounds/SoundManager.hpp"
PlayerStateLaser::PlayerStateLaser()
{
	laser_is_ready = false;
	laser_is_fire = false;
	laser_timer = 0;
}

PlayerStateLaser::~PlayerStateLaser()
{
}

void PlayerStateLaser::Enter()
{

	SoundManager::GetSoundManager().PlayFireLaserSe();
	SoundManager::GetSoundManager().StopSoundCharge();

	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::EternalLaser,
		ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());

	laser_is_ready = false;
	laser_is_fire = false;
	laser_timer = LASER_MAX_TIME;

}

void PlayerStateLaser::Update()
{

	// レーザー開始直後にカメラ向きを反映（初期フレームの向き補正）
	EffectCreator::GetEffectCreator().SetRotateEffect(EffectCreator::EffectType::EternalLaser,
		(VAdd(ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition(), VScale(ObjectAccessor::GetObjectAccessor().GetCameraDirection(), LASER_DISTANCE))));

	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::EternalLaser,
		ObjectAccessor::GetObjectAccessor().GetPlayerHandPosition());

	laser_timer -= LASER_DECREACE_TIME;

	FireEnd();
}

bool PlayerStateLaser::FireEnd()
{
	if (laser_timer <= 0)
	{
		return true;
	}
	return false;
}

void PlayerStateLaser::Exit()
{
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EternalLaser);
}

PlayerStateKind PlayerStateLaser::GetNextState()
{
	if (FireEnd())
	{
        ObjectAccessor::GetObjectAccessor().ChangeCrystalIsBreak();
		return PlayerStateKind::STATE_IDLE;
	}
	else
	{
		return  PlayerStateKind::STATE_LASER;
	}
}