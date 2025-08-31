#include "stdafx.hpp"
#include "Enemy.hpp"
#include "Chase.hpp"
#include "Stage.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "EnemyAnimater.hpp"

Enemy::Enemy()
{
	obj_name = "Enemy";
	enemy_attacktype = 0;
	obj_modelhandle = MV1LoadModel("data/3dmodel/Enemy/Enemy.mv1");
	enemy_handname = MV1SearchFrame(obj_modelhandle, "m1.R");
	enemy_state = STATE_CHASE;
	// 3Dモデルのスケール決定
	MV1SetScale(obj_modelhandle, VGet(ENEMY_SCALE, ENEMY_SCALE, ENEMY_SCALE));
	
	enemy_animater = std::make_shared<EnemyAnimater>(obj_modelhandle, enemy_state);
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	enemy_isaction = false;	
	enemy_ischase = false;
	obj_position = VGet(0, 0, 20.0f);
}
void Enemy::Update()
{
	// 画面に回転量を描画
	clsDx();
	// フレーム名 Mesh_1 のフレームの番号を画面に描画する
	printfDx("positionX%f\n", obj_position.x);
	printfDx("positionY%f\n", obj_position.y);
	printfDx("positionZ%f\n", obj_position.z);
	printfDx("State%d\n", enemy_state);

	UpdateStateAction();
	enemy_animater->Update();

	UpdateAngle();

	SetPosition();
}

void Enemy::UpdateStateAction()  
{  
	switch (enemy_state)  
	{  
	case STATE_IDLE:  
		// No action for idle state  
		break;  

	case STATE_CHARGE:  
		if (enemy_isaction = enemy_animater->GetAmimIsEnd())  
		{  
			enemy_state = STATE_CHASE;  
		}  
		break;  

	case STATE_CHASE:  
		obj_position = enemy_chase->MoveToTarget(obj_position, player_refrence->GetPosition());  

		if (enemy_ischase = enemy_chase->Update(obj_position, player_refrence->GetPosition()))  
		{  
			enemy_attacktype = GetRand(2);  

			if (enemy_attacktype == 0)  
			{  
				enemy_state = STATE_FIREATTACK;  
			}  
			else if (enemy_attacktype == 1)  
			{  
				enemy_state = STATE_WATERATTACK;  
			}  
			else if (enemy_attacktype == 2)  
			{  
				enemy_state = STATE_WINDATTACK;  
			}  
		}  
		break;

	case STATE_FIREATTACK:  
		enemy_isaction = enemy_animater->GetAmimIsEnd();  
		if (enemy_animater->GetAmimFrame() == 60.0f)  
		{  
		}  
		if (enemy_isaction)  
		{  
			enemy_state = STATE_CHARGE;  
		}  
		break;  

	case STATE_WATERATTACK:  
		enemy_isaction = enemy_animater->GetAmimIsEnd();  
		if (enemy_animater->GetAmimFrame() == 20.0f)  
		{  
			// Water attack logic  
		}  
		if (enemy_isaction)  
		{  
			enemy_state = STATE_CHARGE;  
		}  
		break;  

	case STATE_WINDATTACK:  
		enemy_isaction = enemy_animater->GetAmimIsEnd();  
		if (enemy_animater->GetAmimFrame() == 50.0f)  
		{  
			// Wind attack logic  
		}  
		if (enemy_isaction)  
		{  
			enemy_state = STATE_CHARGE;  
		}  
		break;  

	default:  
		// Handle unexpected states  
		break;  
	}  
}

void Enemy::UpdateAngle()
{
	// ３Ｄモデル２から３Ｄモデル１に向かうベクトルを算出
	VECTOR angleVector = VSub(player_refrence->GetPosition(), obj_position);

	// atan2 を使用して角度を取得
	float angle = atan2(angleVector.x, angleVector.z);

	// atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F )を
	// 足した値を３Ｄモデルの Y軸回転値として設定
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

void Enemy::SetPosition()
{
	//プレイヤーのモデルの設置
	MV1SetPosition(obj_modelhandle, obj_position);
}

void Enemy::Draw()
{
	MV1DrawModel(obj_modelhandle);
}