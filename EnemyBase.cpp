#include"DxLib.h"
#include"Stage.hpp"
#include "EnemyAnimater.hpp"
#include"EnemyBase.hpp"

EnemyBase::EnemyBase()
	:enemy_modelhandle(0)
	,position(VGet(-10.0f, 0.0f,10.0f))
	,angleVector(VGet(0,0,0))
	,angle(0)
	,action_iswater(false)
	,action_isfire(false)
	,action_iswind(false)
	,attackType(0)
{
	enemy_modelhandle = MV1LoadModel("data/3dmodel/Enemy/Enemy.mv1");
	// 3Dモデルのスケール決定
	MV1SetScale(enemy_modelhandle, VGet(Scale, Scale, Scale));
	// 3Dモデルの位置決定
	MV1SetPosition(enemy_modelhandle, position);
	//インスタンス生成
	state = STATE_CHARGE;
	enemy_animater = std::make_shared<EnemyAnimater>(enemy_modelhandle,state);
	enemyattack_manager = std::make_shared<EnemyAttackManager>(enemy_modelhandle);
	
}

EnemyBase::~EnemyBase()
{
}

/// @brief 
///初期化
void EnemyBase::Initialize()
{

}
/// @brief 
/// 更新
/// @param playerpos 
/// @param stage 
void EnemyBase::Update(const VECTOR& playerpos, Stage& stage)
{	
	// 画面に回転量を描画
	clsDx();
	// フレーム名 Mesh_1 のフレームの番号を画面に描画する
	printfDx("positionX%f\n", position.x);
	printfDx("positionY%f\n", position.y);
	printfDx("positionZ%f\n", position.z);
	printfDx("State%d\n", state);

	UpdateAngle(playerpos);
	UpdateStateAction(playerpos);
	enemy_animater->Update();

	Move(position,stage);
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

		break;

	case STATE_FIREATTACK:

		position = enemyattack_manager->FireAttack(playerpos, position, angleVector);
		action_isfire = enemyattack_manager->IsFireAttack();
		if (action_isfire)
		{
			state = STATE_CHARGE;
		}
		break;
	case STATE_WATERATTACK:
		position = enemyattack_manager->WaterAttack(playerpos, position, angleVector);
		action_iswater = enemyattack_manager->IsWaterAttack();
		if (action_iswater)
		{
			state = STATE_CHARGE;
		}
		break;
	case STATE_WINDATTACK:
		position = enemyattack_manager->WindAttack(playerpos, position, angleVector);
		action_iswind = enemyattack_manager->IsWindAttack();
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
	MV1DrawModel(enemy_modelhandle);
}