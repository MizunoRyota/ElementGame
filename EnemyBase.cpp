#include"DxLib.h"
#include"Stage.hpp"
#include "Bullet.hpp"
#include "BulletManager.hpp"
#include "EnemyAnimater.hpp"
#include "Chase.hpp"
#include"EnemyBase.hpp"
#include "Sound.hpp"
EnemyBase::EnemyBase()
	:enemy_modelhandle(0)
	,position(VGet(0.0f, 0.0f,15.0f))
	,angleVector(VGet(0,0,0))
	,angle(0)
	,action_iswater(false)
	,action_isfire(false)
	,action_iswind(false)
	,attackType(0)
	,hand_position(VGet(0,0,0))
	, action_ischase(false)
	,bullet_startpos(VGet(0,0,0))
	, takedamage_cooldowntimer(0.0f)
{
	enemy_modelhandle = MV1LoadModel("data/3dmodel/Enemy/Enemy.mv1");
	// 3Dモデルのスケール決定
	MV1SetScale(enemy_modelhandle, VGet(Scale, Scale, Scale));
	// 3Dモデルの位置決定
	MV1SetPosition(enemy_modelhandle, position);
	hand_name = MV1SearchFrame(enemy_modelhandle, "m1.R");

	//インスタンス生成
	state = STATE_CHARGE;
	enemy_animater = std::make_shared<EnemyAnimater>(enemy_modelhandle,state);
	enemyattack_manager = std::make_shared<EnemyAttackManager>(enemy_modelhandle);
	enemy_chase = std::make_shared<Chase>();
	sound_manager = std::make_shared<Sound>();
	hand_position = MV1GetFramePosition(enemy_modelhandle, hand_name);
	hp = 100; // 初期HP設定
}

EnemyBase::~EnemyBase()
{
}

/// @brief 
///初期化
void EnemyBase::Initialize()
{
	state = STATE_IDLE;
	hp = 200; // 初期HP設定
	position = VGet(0.0f, 0.0f, 15.0f);
	angleVector = VGet(0, 0, 0);
	angle = 0;
	action_iswater = false;
	action_isfire = false;
	action_iswind = false;
	attackType = 0;
	action_ischase = false;
	bullet_startpos = VGet(0, 0, 0);
	takedamage_cooldowntimer = 0.0f;
	// 3Dモデルの位置決定
	MV1SetPosition(enemy_modelhandle, position);
	// 3Dモデルのスケール決定
	MV1SetScale(enemy_modelhandle, VGet(Scale, Scale, Scale));
	// 3Dモデルの回転を初期化
	MV1SetRotationXYZ(enemy_modelhandle, VGet(0.0f, 0.0f, 0.0f));
}
/// @brief 
/// 更新
/// @param playerpos 
/// @param stage 
void EnemyBase::Update(const VECTOR& playerpos, Stage& stage)
{	
	// クールタイムタイマー更新
	if (takedamage_cooldowntimer > 0.0f) {
		takedamage_cooldowntimer -= 1.0f; // 60FPS想定
		if (takedamage_cooldowntimer < 0.0f) takedamage_cooldowntimer = 0.0f;
	}
	//// 画面に回転量を描画
	//clsDx();
	//// フレーム名 Mesh_1 のフレームの番号を画面に描画する
	//printfDx("positionX%f\n", position.x);
	//printfDx("positionY%f\n", position.y);
	//printfDx("positionZ%f\n", position.z);
	//printfDx("State%d\n", state);

	UpdateAngle(playerpos);
	UpdateStateAction(playerpos);
	enemy_animater->Update();

	Move(position,stage);
	hand_position = MV1GetFramePosition(enemy_modelhandle, hand_name);

}

void EnemyBase::FireBullet(const float bullet_speed)
{
	hand_position = MV1GetFramePosition(enemy_modelhandle, hand_name);
	hand_position = VAdd(hand_position, VGet(0,-1.0f,0));

	bullet_manager->Shot(hand_position,angleVector, bullet_speed);
}

void EnemyBase::TakeDamage(const int damage)
{
	if (takedamage_cooldowntimer > 0.0f) {
		// クールタイム中はダメージ無効
		return;
	}
	sound_manager->PlayOnenemy();
	// ダメージを受けたときの処理
	hp -= damage;
	takedamage_cooldowntimer = takedamage_cooldown;
}

/// @brief 
/// 向く方向計算
/// @param playerpos 
void EnemyBase::UpdateAngle(const VECTOR& playerpos)
{
	// ３Ｄモデル２から３Ｄモデル１に向かうベクトルを算出
	angleVector = VSub(playerpos, position);

	// atan2 を使用して角度を取得
	angle = atan2(angleVector.x, angleVector.z);

	// atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F )を
	// 足した値を３Ｄモデルの Y軸回転値として設定
	MV1SetRotationXYZ(enemy_modelhandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

void EnemyBase::UpdateStateAction(const VECTOR& playerpos)
{
	switch (state)
	{
	case STATE_IDLE:

		break;
	case STATE_CHARGE:
		enemyattack_manager->InitializeFireAttack();
		enemyattack_manager->InitializeWaterAttack();
		enemyattack_manager->InitializeWindAttack();

		state = STATE_CHASE;
		break;
	case STATE_CHASE:

		position = enemy_chase->MoveToTarget(position, playerpos);
		action_ischase = enemy_chase->Update(position,playerpos);
		if (action_ischase)
		{
			attackType = GetRand(2);

			if (attackType == 0)
			{
				state = STATE_FIREATTACK; break;
			}
			else if (attackType == 1)
			{
				state = STATE_WATERATTACK; break;
			}
			else if (attackType == 2)
			{
				state = STATE_WINDATTACK; break;
			}

		}

		break;
	case STATE_FIREATTACK:


		action_isfire = enemy_animater->GetAmimIsEnd();
		if (enemy_animater->GetAmimFrame()==60.0f)
		{
			FireBullet(firebullet_speed);
		}
		if (action_isfire)
		{
			state = STATE_CHARGE;
		}
		break;
	case STATE_WATERATTACK:

		action_iswater = enemy_animater->GetAmimIsEnd();
		if (enemy_animater->GetAmimFrame() == 20.0f)
		{
			FireBullet(waterbullet_speed);
		}
		if (action_iswater)
		{
			state = STATE_CHARGE;
		}
		break;
	case STATE_WINDATTACK:

		action_iswind = enemy_animater->GetAmimIsEnd();
		if (enemy_animater->GetAmimFrame() == 50.0f)
		{
			FireBullet(windbullet_speed);
		}
		if (action_iswind)
		{
			state = STATE_CHARGE;
		}

		break;
	default:

		break;
	}
}

/// @brief 
/// ポジションをセット
/// @param MoveVector 
/// @param stage 
void EnemyBase::Move(const VECTOR& MoveVector, Stage& stage)
{
	// 当たり判定をして、新しい座標を保存する
	//position = stage.CheckEnemyCollision(*this, MoveVector);
	MV1SetPosition(enemy_modelhandle, position);
}

/// @brief 
/// 表示関数
/// @param playerpos 
void EnemyBase::Draw()
{
	enemyattack_manager->DebugDraw();
	bullet_manager->Draw();
	MV1DrawModel(enemy_modelhandle);
}

void EnemyBase::UpdateGameClear()
{
	state = STATE_DIE;
	position = VGet(0.0f, 0.0f, 15.0f);
	enemy_animater->Update();

	MV1SetPosition(enemy_modelhandle, position);
}

void EnemyBase::UpdateGameTitle()
{
		state = STATE_IDLE;
	position = VGet(0.0f, 0.0f, 15.0f);
	enemy_animater->Update();
	MV1SetPosition(enemy_modelhandle, position);
}

void EnemyBase::UpdateGameOver()
{
	state = STATE_JUMPATTACK;
	position = VGet(0.0f, 0.0f, 15.0f);
	enemy_animater->Update();
	MV1SetPosition(enemy_modelhandle, position);
}