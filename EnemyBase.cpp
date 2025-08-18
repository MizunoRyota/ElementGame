#include"DxLib.h"
#include"Stage.hpp"
#include"EnemyBase.hpp"

EnemyBase::EnemyBase()
	:EnemyHandle(0)
	,position(VGet(-10.0f, 0.0f,10.0f))
	,angleVector(VGet(0,0,0))
	,angle(0)
	,action_iswater(false)
	,action_isfire(false)
	,action_iswind(false)
	,attackType(0)
{

	EnemyHandle = MV1LoadModel("data/3dmodel/Enemy/roboblue.mv1");
	// 3Dモデルのスケール決定
	MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
	// 3Dモデルの位置決定
	MV1SetPosition(EnemyHandle, position);
	//インスタンス生成
	enemyanimation_manager = std::make_shared<EnemyAnimationManager>(EnemyHandle);
	enemyattack_manager = std::make_shared<EnemyAttackManager>(EnemyHandle);
	state = STATE_CHARGE;
}
EnemyBase::~EnemyBase()
{
}

/// @brief 
///初期化
void EnemyBase::Initialize()
{
	//エネミーのアニメーション初期化
	enemyanimation_manager->Initialize();
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

	enemyanimation_manager->Update();
	UpdateAngle(playerpos);
	UpdateStateAction(playerpos);
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
	MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

void EnemyBase::UpdateStateAction(const VECTOR& playerpos)
{
	switch (state)
	{
	case EnemyBase::STATE_UNKNOWN:

		break;
	case EnemyBase::STATE_IDLE:

		break;
	case EnemyBase::STATE_CHARGE:
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
	case EnemyBase::STATE_SLIDE:
		break;

	case EnemyBase::STATE_FIREATTACK:
		position = enemyattack_manager->FireAttack(playerpos, position, angleVector);
		action_isfire = enemyattack_manager->IsFireAttack();
		if (action_isfire)
		{
			state = STATE_CHARGE;
		}
		break;
	case EnemyBase::STATE_WATERATTACK:
		position = enemyattack_manager->WaterAttack(playerpos, position, angleVector);
		action_iswater = enemyattack_manager->IsWaterAttack();
		if (action_iswater)
		{
			state = STATE_CHARGE;
		}
		break;
	case EnemyBase::STATE_WINDATTACK:

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
	MV1SetPosition(EnemyHandle, position);
}

/// @brief 
/// 表示関数
/// @param playerpos 
void EnemyBase::Draw()
{
	enemyattack_manager->DebugDraw();
	MV1DrawModel(EnemyHandle);
}