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
	this->anim_currentstate.anim_animnum = -1;
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
	animation_data[static_cast<int>(AnimKind::WalkBack)] = AnimationState(static_cast<int>(AnimKind::WalkBack),(static_cast<int>(AnimKind::WalkBack)), 0, 0, 0.5f,true);
	animation_data[static_cast<int>(AnimKind::Die)] = AnimationState(static_cast<int>(AnimKind::Die), (static_cast<int>(AnimKind::Die)), 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::SpecialCharge)] = AnimationState(static_cast<int>(AnimKind::SpecialCharge), (static_cast<int>(AnimKind::SpecialCharge)), 0, 0, 0.25f,true);
	animation_data[static_cast<int>(AnimKind::Float)] = AnimationState(static_cast<int>(AnimKind::Float), (static_cast<int>(AnimKind::Float)), 0, 0, 0.5f, true);
	animation_data[static_cast<int>(AnimKind::SpecialAttack)] = AnimationState(static_cast<int>(AnimKind::SpecialAttack), (static_cast<int>(AnimKind::SpecialAttack)), 0, 0, 0.5f, false);
	animation_data[static_cast<int>(AnimKind::RunLeft)] = AnimationState(static_cast<int>(AnimKind::RunLeft), (static_cast<int>(AnimKind::RunLeft)), 0, 0, 0.5f,true);
	animation_data[static_cast<int>(AnimKind::Charge)] = AnimationState(static_cast<int>(AnimKind::Charge), (static_cast<int>(AnimKind::Charge)), 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::RunRight)] = AnimationState(static_cast<int>(AnimKind::RunRight), (static_cast<int>(AnimKind::RunRight)), 0, 0, 0.5f,true);
	animation_data[static_cast<int>(AnimKind::FireAttack)] = AnimationState(static_cast<int>(AnimKind::FireAttack), (static_cast<int>(AnimKind::FireAttack)), 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::WaterAttack)] = AnimationState(static_cast<int>(AnimKind::WaterAttack), (static_cast<int>(AnimKind::WaterAttack)), 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::WindAttack)] = AnimationState(static_cast<int>(AnimKind::WindAttack), (static_cast<int>(AnimKind::WindAttack)), 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::JumpAttack)] = AnimationState(static_cast<int>(AnimKind::JumpAttack), (static_cast<int>(AnimKind::JumpAttack)), 0, 0, 0.5f,false);
	animation_data[static_cast<int>(AnimKind::Idle)] = AnimationState(static_cast<int>(AnimKind::Idle), (static_cast<int>(AnimKind::Idle)), 0, 0, 0.25f,true);
	animation_data[static_cast<int>(AnimKind::Chase)] = AnimationState(static_cast<int>(AnimKind::Chase), (static_cast<int>(AnimKind::Chase)), 0, 0, 0.5f,true);
	animation_data[static_cast<int>(AnimKind::OnDamage)] = AnimationState(static_cast<int>(AnimKind::OnDamage), (static_cast<int>(AnimKind::OnDamage)), 0, 0, 0.5f,false);
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
	case STATE_ONDAMAGE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::OnDamage)));
		break;
	case STATE_WALKBACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::WalkBack)));
		break;
	case STATE_DIE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Die)));
		break;
	case STATE_SPECIAL_CHARGE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::SpecialCharge)));
		break;
	case STATE_FLOAT:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Float)));
		break;
	case STATE_SPECIALATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::SpecialAttack)));
		break;
	case STATE_RUNLEFT:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::RunLeft)));
		break;
	case STATE_CHARGE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Charge)));
		break;
	case STATE_RUNRIGHT:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::RunRight)));
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
	case STATE_CHASE:
		ChangeMotion(animation_data.at(static_cast<int>(AnimKind::Chase)));
		break;
	default:

		break;
	}
}