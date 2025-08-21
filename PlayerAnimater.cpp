#include"DxLib.h"
#include<cmath>
#include "AnimationData.hpp"
#include "PlayerState.hpp"
#include"PlayerAnimater.hpp"

PlayerAnimater::PlayerAnimater(int modelhandle, PlayerState& playerstate)
	:AnimaterBase(modelhandle)
	, player_state(playerstate)
{
	////アニメーションのステート初期化
	this->prevState.AnimationNum = -1;
	this->prevState.AnimTime = 0;
	this->prevState.PlayAnimSpeed = 0;
	this->prevState.TotalAnimationTime = 0;
	this->prevState.animaton_isloop = false;
	this->currentState.AnimationNum = 0;
	this->currentState.AnimTime = 0;
	this->currentState.PlayAnimSpeed = 0;
	this->currentState.TotalAnimationTime = 0;
	this->currentState.animaton_isloop = false;
	this->modelHandle = modelhandle;
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