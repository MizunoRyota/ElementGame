#include "stdafx.hpp"
#include "Enemy.hpp"
#include "Chase.hpp"
#include "Dodge.hpp"
#include "Stage.hpp"
#include "Player.hpp"
#include "BulletFire.hpp"
#include "EnemyAnimater.hpp"
#include "SpecialAttack.hpp"
#include "EnemyMove.hpp"

Enemy::Enemy()
{
	obj_name = "Enemy";
	enemy_attacktype = 0;
	obj_modelhandle = MV1LoadModel("data/3dmodel/Enemy/Enemy4.mv1");
	character_handname = MV1SearchFrame(obj_modelhandle, "m1.R");

	enemy_state = STATE_CHARGE;
	MV1SetScale(obj_modelhandle, VGet(ENEMY_SCALE, ENEMY_SCALE, ENEMY_SCALE));

	enemy_animater = std::make_shared<EnemyAnimater>(obj_modelhandle, enemy_state);
	enemy_bullet = std::make_shared<BulletFire>();
	enemy_dodge = std::make_shared<Dodge>();
	enemy_specialattack = std::make_shared<SpecialAttack>();
	enemy_move = std::make_shared<EnemyMove>();

	// ダメージクールタイム設定（TAKEDAMAGE_COOLDOWN は float なので int 化）
	ConfigureDamageCooldown(static_cast<int>(TAKEDAMAGE_COOLDOWN));

}

Enemy::~Enemy() {}

void Enemy::Initialize()
{
	enemy_isaction = false;
	enemy_ischase = false;
	obj_position = VGet(0, 0, 20.0f);
	// HP 初期値（必要なら適切な値を設定）
	if (obj_hp <= 0) obj_hp = 100; // 仮: 敵の最大 HP が未定義なら暫定
}

void Enemy::Update()
{
	clsDx();
	printfDx("positionX%f\n", obj_position.x);
	printfDx("positionY%f\n", obj_position.y);
	printfDx("positionZ%f\n", obj_position.z);
	printfDx("State%d\n", enemy_state);
	printfDx("enemyHp%d\n", obj_hp);

	enemy_animater->Update();
	UpdateAngle();
	UpdateStateAction();
	enemy_bullet->FireUpdate();
	SetPosition();

	//無敵タイマー減算
	TickDamageCooldown();
}

void Enemy::UpdateStateAction()  
{  
	switch (enemy_state)  
	{  
	case STATE_IDLE:  
	
		obj_position = enemy_move->MoveToOrigin(obj_position);

		break;  

	case STATE_CHARGE:  
		if (enemy_isaction = enemy_animater->GetAmimIsEnd())  
		{  
			enemy_attacktype = GetRand(1);

			if (enemy_attacktype == 0)
			{
				enemy_state = STATE_RUNLEFT;
			}
			else if (enemy_attacktype == 1)
			{
				enemy_state = STATE_RUNRIGHT;
			}

		}  
		break;  

	case STATE_RUNLEFT:  

		obj_position = enemy_dodge->DodgeEnemy(obj_position, obj_direction,enemy_state);

		if (enemy_dodge->GetIsDodgeEnd())
		{
			enemy_state = STATE_CHASE;
		}

		break;

	case STATE_RUNRIGHT:  

		obj_position = enemy_dodge->DodgeEnemy(obj_position, obj_direction,enemy_state);

		if (enemy_dodge->GetIsDodgeEnd())
		{
			enemy_state = STATE_CHASE;
		}

		break;

	case STATE_CHASE:  
		obj_position = enemy_move->MoveToTarget(obj_position, player_refrence->GetPosition());  

		if (enemy_ischase = enemy_chase->RangeWithin(obj_position, player_refrence->GetPosition()))  
		{  
			//enemy_attacktype = GetRand(2);  

			//if (enemy_attacktype == 0)  
			//{  
			//	enemy_state = STATE_FIREATTACK;  
			//}  
			//else if (enemy_attacktype == 1)  
			//{  
				//enemy_state = STATE_WATERATTACK;
			//}  
			//else if (enemy_attacktype == 2)  
			//{  
				enemy_state = STATE_WINDATTACK;  
			//}  
		}  

		break;

	case STATE_FIREATTACK:  

		if (enemy_animater->GetAmimFrame() == 60.0f)  
		{  

			character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname);
			character_handposition = VAdd(character_handposition, VGet(0, BULLET_HIGHT, 0));

			enemy_bullet->FireStraight(character_handposition,obj_direction,FIREBULLET_SPEED);

		}  

		if (enemy_isaction = enemy_animater->GetAmimIsEnd())
		{  
			enemy_state = STATE_CHARGE;  
		}  

		break;  

	case STATE_WATERATTACK:  
		if (enemy_animater->GetAmimFrame() == 20.0f)  
		{  
			character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname);
			character_handposition = VAdd(character_handposition,VGet(0, BULLET_HIGHT, 0));

			enemy_bullet->FireDiffusion(character_handposition, obj_direction, WATERBULLET_SPEED);
		
		}  
		if (enemy_isaction = enemy_animater->GetAmimIsEnd())
		{  
			enemy_state = STATE_CHARGE;  
		}  

		break;  

	case STATE_WINDATTACK:  
		
		if (enemy_animater->GetAmimFrame() >= 20.0f)  
		{
			character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname);

			// 変更: プレイヤー参照を渡す
			enemy_bullet->FireHoming(character_handposition, obj_direction, FIREBULLET_SPEED, player_refrence);
		}  
		if (enemy_isaction = enemy_animater->GetAmimIsEnd())
		{  
			enemy_state = STATE_CHARGE;  
		}  
		break;

	case STATE_WALKBACK:

		break;

	case STATE_FLOAT:

		obj_position = enemy_move->MoveToOrigin(obj_position);

		if (enemy_move->GetIsOrigin())
		{
			enemy_state = STATE_GROUNDATTACK;
		}

		break;

	case STATE_GROUNDATTACK:
		
		obj_position = enemy_move->MoveToSky(obj_position);

		if (enemy_isaction = enemy_animater->GetAmimIsEnd())
		{
			enemy_state = STATE_SPECIALATTACK;
		}

		break;
	case STATE_SPECIALATTACK:

		if (enemy_animater->GetAmimFrame() == 35.0f)
		{
			character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname);
			character_handposition = VAdd(character_handposition, VGet(0, BULLET_HIGHT, 0));
			enemy_bullet->FireSpecialAttack	(character_handposition, obj_direction, FIREBULLET_SPEED);
		}

		if (enemy_isaction = enemy_animater->GetAmimIsEnd())
		{
			enemy_state = STATE_CHARGE;
		}

		break;

	case STATE_JUMPATTACK:

		break;

	default:  
		// Handle unexpected states  
		break;  
	}  
}

void Enemy::UpdateAngle()
{
	// ３Ｄモデル２から３Ｄモデル１に向かうベクトルを算出
	 obj_direction = VSub(player_refrence->GetPosition(), obj_position);

	// atan2 を使用して角度を取得
	float angle = atan2(obj_direction.x, obj_direction.z);

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