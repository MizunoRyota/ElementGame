#include "stdafx.hpp"
#include "AnimationData.hpp"
#include "EnemyState.hpp"
#include"EnemyAnimater.hpp"

EnemyAnimater::EnemyAnimater(int anim_modelhandle ,  EnemyState& enemystate)
	:AnimaterBase(anim_modelhandle)
	,enemy_state(enemystate)
{
	////アニメーションのステート初期化
	this->anim_prevstate.anim_animnum = -1;
	this->anim_prevstate.anim_nowtime = 0;
	this->anim_prevstate.anim_playspeed = 0;
	this->anim_prevstate.anim_totaltime = 0;
	this->anim_prevstate.anim_isloop = false;
	this->anim_currentstate.anim_animnum = 0;
	this->anim_currentstate.anim_nowtime = 0;
	this->anim_currentstate.anim_playspeed = 0;
	this->anim_currentstate.anim_totaltime = 0;
	this->anim_currentstate.anim_isloop = false;
	this->anim_modelhandle = anim_modelhandle;
	InitializeAnimationData();
}
EnemyAnimater::~EnemyAnimater()
{}

void EnemyAnimater::InitializeAnimationData()
{
	animation_data[static_cast<int>(AnimKind::Chase)] = AnimationState(static_cast<int>(AnimKind::Chase),0, 0, 0, 0.5f,true);
	animation_data[static_cast<int>(AnimKind::OnDamage)] = AnimationState(static_cast<int>(AnimKind::OnDamage),1, 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::Walkback)] = AnimationState(static_cast<int>(AnimKind::Walkback),2, 0, 0, 0.5f,true);
	animation_data[static_cast<int>(AnimKind::Die)] = AnimationState(static_cast<int>(AnimKind::Die),3, 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::GroundAttack)] = AnimationState(static_cast<int>(AnimKind::GroundAttack),4, 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::RunLeft)] = AnimationState(static_cast<int>(AnimKind::RunLeft),5, 0, 0, 0.5f,true);
	animation_data[static_cast<int>(AnimKind::Charge)] = AnimationState(static_cast<int>(AnimKind::Charge),6, 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::RunRight)] = AnimationState(static_cast<int>(AnimKind::RunRight),7, 0, 0, 0.5f,true);
	animation_data[static_cast<int>(AnimKind::WindAttack)] = AnimationState(static_cast<int>(AnimKind::WindAttack),8, 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::WaterAttack)] = AnimationState(static_cast<int>(AnimKind::WaterAttack),9, 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::FireAttack)] = AnimationState(static_cast<int>(AnimKind::FireAttack),10, 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::JumpAttack)] = AnimationState(static_cast<int>(AnimKind::JumpAttack),11, 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::Idle)] = AnimationState(static_cast<int>(AnimKind::Idle),12, 0, 0, 0.5f,true);
}

void EnemyAnimater::Update()
{
	SwitchAnimation();
	UpdateAnimation();


}

void EnemyAnimater::SwitchAnimation()
{

	switch (enemy_state)
	{
	case STATE_CHASE:

		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Chase)));

		break;
	case STATE_ONDAMAGE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::OnDamage)));
		break;
	case STATE_WALKBACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Walkback)));
		break;
	case STATE_DIE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Die)));
		break;
	case STATE_GROUNDATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::GroundAttack)));
		break;

	case STATE_RUNLEFT:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::RunLeft)));
		break;
	case STATE_RUNRIGHT:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::RunRight)));
		break;
	case STATE_CHARGE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Charge)));

		break;

	case STATE_WINDATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::WindAttack)));

		break;
	case STATE_WATERATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::WaterAttack)));

		break;
	case STATE_FIREATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::FireAttack)));

		break;
	case STATE_JUMPATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::JumpAttack)));

		break;
	case STATE_IDLE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Idle)));
		break;
	default:

		break;
		
	}
}