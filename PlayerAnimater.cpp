#include "stdafx.hpp"
#include "AnimationData.hpp"
#include "PlayerStateKind.hpp"
#include"PlayerAnimater.hpp"

PlayerAnimater::PlayerAnimater(int modelhandle, PlayerStateKind& playerstate)
	:AnimaterBase(modelhandle)
	, player_state(playerstate)
{
	////アニメーションのステート初期化
	this->anim_prevstate.anim_animnum = -1;
	this->anim_prevstate.anim_nowtime = 0;
	this->anim_prevstate.anim_playspeed = 0;
	this->anim_prevstate.anim_totaltime = 0;
	this->anim_prevstate.anim_is_loop = false;
	this->anim_prevstate.anim_attachindex = -1;
	this->anim_currentstate.anim_animnum = 0;
	this->anim_currentstate.anim_nowtime = 0;
	this->anim_currentstate.anim_playspeed = 0;
	this->anim_currentstate.anim_totaltime = 0;
	this->anim_currentstate.anim_is_loop = false;
	this->anim_currentstate.anim_attachindex = -1;
	this->anim_modelhandle = modelhandle;
	InitializeAnimationData();
}
PlayerAnimater::~PlayerAnimater()
{
}

void PlayerAnimater::InitializeAnimationData()
{
	animation_data[static_cast<int>(PlayerStateKind::STATE_ATTACK)] = AnimationState(static_cast<int>(PlayerStateKind::STATE_ATTACK), 7, 0, 0, 0.5f, true);
	animation_data[static_cast<int>(PlayerStateKind::STATE_IDLE)] = AnimationState(static_cast<int>(PlayerStateKind::STATE_IDLE), 9, 0, 0, 0.5f, true);
}

void PlayerAnimater::Update()
{
	SwitchAnimation();
	UpdateAnimation();
}

void PlayerAnimater::SwitchAnimation()
{
	switch (player_state)
	{
	case PlayerStateKind::STATE_ATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(PlayerStateKind::STATE_ATTACK)));
		break;
	case PlayerStateKind::STATE_IDLE:
		ChangeMotion(animation_data.at(static_cast<int>(PlayerStateKind::STATE_IDLE)));
		break;
	case PlayerStateKind::STATE_LASER:
		ChangeMotion(animation_data.at(static_cast<int>(PlayerStateKind::STATE_ATTACK)));
		break;

	default:
		break;
	}
}