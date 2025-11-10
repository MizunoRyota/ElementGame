#include "stdafx.hpp"
#include "AnimationData.hpp"
#include "PlayerState.hpp"
#include"PlayerAnimater.hpp"

PlayerAnimater::PlayerAnimater(int modelhandle, PlayerState& playerstate)
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
	animation_data[static_cast<int>(AnimKind::Idle)] = AnimationState(static_cast<int>(AnimKind::Idle), 9, 0, 0, 0.5f, true);
	animation_data[static_cast<int>(AnimKind::Attack)] = AnimationState(static_cast<int>(AnimKind::Attack), 7, 0, 0, 0.5f, true);
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
	case STATE_HANDIDLE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Idle)));
		break;
	case STATE_ATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Attack)));
		break;
	default:

		break;
	}
}