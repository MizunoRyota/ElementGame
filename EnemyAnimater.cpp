#include "stdafx.hpp"
#include "AnimationData.hpp"
#include "EnemyStateKind.hpp"
#include"EnemyAnimater.hpp"

EnemyAnimater::EnemyAnimater(int anim_modelhandle ,  EnemyStateKind& enemystate)
	:AnimaterBase(anim_modelhandle)
	,enemy_state(enemystate)
{
	////アニメーションのステート初期化
	this->anim_prevstate.anim_animnum = -1;
	this->anim_prevstate.anim_nowtime = 0;
	this->anim_prevstate.anim_playspeed = 0;
	this->anim_prevstate.anim_totaltime = 0;
	this->anim_prevstate.anim_is_loop = false;
	this->anim_currentstate.anim_animnum = -1;
	this->anim_currentstate.anim_nowtime = 0;
	this->anim_currentstate.anim_playspeed = 0;
	this->anim_currentstate.anim_totaltime = 0;
	this->anim_currentstate.anim_is_loop = false;
	this->anim_modelhandle = anim_modelhandle;
	InitializeAnimationData();
}
EnemyAnimater::~EnemyAnimater()
{}

void EnemyAnimater::InitializeAnimationData()
{
	animation_data[static_cast<int>(EnemyStateKind::STATE_STUN)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_STUN), (static_cast<int>(EnemyStateKind::STATE_STUN)), 0, 0, DEFAULT_ANIMATION_SPEED, true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_WALKBACK)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_WALKBACK),(static_cast<int>(EnemyStateKind::STATE_WALKBACK)), 0, 0, DEFAULT_ANIMATION_SPEED,true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_DIE)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_DIE), (static_cast<int>(EnemyStateKind::STATE_DIE)), 0, 0, DEFAULT_ANIMATION_SPEED,false);
	animation_data[static_cast<int>(EnemyStateKind::STATE_SPECIAL_CHARGE)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_SPECIAL_CHARGE), (static_cast<int>(EnemyStateKind::STATE_SPECIAL_CHARGE)), 0, 0, DEFAULT_ANIMATION_SPEED,true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_FLOAT)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_FLOAT), (static_cast<int>(EnemyStateKind::STATE_FLOAT)), 0, 0, DEFAULT_ANIMATION_SPEED, true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_SPECIALATTACK)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_SPECIALATTACK), (static_cast<int>(EnemyStateKind::STATE_SPECIALATTACK)), 0, 0, SPECIALATTACK_ANIMATION_SPEED, true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_RUNLEFT)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_RUNLEFT), (static_cast<int>(EnemyStateKind::STATE_RUNLEFT)), 0, 0, DEFAULT_ANIMATION_SPEED,true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_CHARGE)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_CHARGE), (static_cast<int>(EnemyStateKind::STATE_CHARGE)), 0, 0, DEFAULT_ANIMATION_SPEED,false);
	animation_data[static_cast<int>(EnemyStateKind::STATE_RUNRIGHT)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_RUNRIGHT), (static_cast<int>(EnemyStateKind::STATE_RUNRIGHT)), 0, 0, DEFAULT_ANIMATION_SPEED,true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_FIREATTACK)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_FIREATTACK), (static_cast<int>(EnemyStateKind::STATE_FIREATTACK)), 0, 0, DEFAULT_ANIMATION_SPEED,false);
	animation_data[static_cast<int>(EnemyStateKind::STATE_WATERATTACK)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_WATERATTACK), (static_cast<int>(EnemyStateKind::STATE_WATERATTACK)), 0, 0, DEFAULT_ANIMATION_SPEED,false);
	animation_data[static_cast<int>(EnemyStateKind::STATE_WINDATTACK)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_WINDATTACK), (static_cast<int>(EnemyStateKind::STATE_WINDATTACK)), 0, 0, DEFAULT_ANIMATION_SPEED,false);
	animation_data[static_cast<int>(EnemyStateKind::STATE_JUMPATTACK)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_JUMPATTACK), (static_cast<int>(EnemyStateKind::STATE_JUMPATTACK)), 0, 0, DEFAULT_ANIMATION_SPEED,false);
	animation_data[static_cast<int>(EnemyStateKind::STATE_IDLE)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_IDLE), (static_cast<int>(EnemyStateKind::STATE_IDLE)), 0, 0, DEFAULT_ANIMATION_SPEED,true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_CHASE)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_CHASE), (static_cast<int>(EnemyStateKind::STATE_CHASE)), 0, 0, DEFAULT_ANIMATION_SPEED,true);
	animation_data[static_cast<int>(EnemyStateKind::STATE_ONDAMAGE)] = AnimationState(static_cast<int>(EnemyStateKind::STATE_ONDAMAGE), (static_cast<int>(EnemyStateKind::STATE_ONDAMAGE)), 0, 0, DEFAULT_ANIMATION_SPEED,false);
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
	case EnemyStateKind::STATE_STUN:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_STUN)));
		break;
	case EnemyStateKind::STATE_ONDAMAGE:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_ONDAMAGE)));
		break;
	case EnemyStateKind::STATE_WALKBACK:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_WALKBACK)));
		break;
	case EnemyStateKind::STATE_DIE:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_DIE)));
		break;
	case EnemyStateKind::STATE_SPECIAL_CHARGE:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_SPECIAL_CHARGE)));
		break;
	case EnemyStateKind::STATE_FLOAT:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_FLOAT)));
		break;
	case EnemyStateKind::STATE_SPECIALATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_SPECIALATTACK)));
		break;
	case EnemyStateKind::STATE_RUNLEFT:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_RUNLEFT)));
		break;
	case EnemyStateKind::STATE_CHARGE:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_CHARGE)));
		break;
	case EnemyStateKind::STATE_RUNRIGHT:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_RUNRIGHT)));
		break;
	case EnemyStateKind::STATE_WINDATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_WINDATTACK)));
		break;
	case EnemyStateKind::STATE_WATERATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_WATERATTACK)));
		break;
	case EnemyStateKind::STATE_FIREATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_FIREATTACK)));
		break;
	case EnemyStateKind::STATE_JUMPATTACK:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_JUMPATTACK)));
		break;
	case EnemyStateKind::STATE_IDLE:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_IDLE)));
		break;
	case EnemyStateKind::STATE_CHASE:
		ChangeMotion(animation_data.at(static_cast<int>(EnemyStateKind::STATE_CHASE)));
		break;
	default:

		break;
	}
}