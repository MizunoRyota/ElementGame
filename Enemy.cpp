#include "stdafx.hpp"
#include "Enemy.hpp"
#include "AnimaterBase.hpp"
#include "EnemyAnimater.hpp"
#include "EffectCreator.hpp"
#include "EnemyStateBase.hpp"
#include "src/EnemyState/EnemyStateIdle.hpp"
#include "src/EnemyState/EnemyStateCharge.hpp"
#include "src/EnemyState/EnemyStateDodge.hpp"
#include "src/EnemyState/EnemyStateChase.hpp"
#include "src/EnemyState/StateFireAttack.hpp"
#include "src/EnemyState/StateWindAttack.hpp"
#include "src/EnemyState/StateWaterAttack.hpp"
#include "src/EnemyState/EnemyStateFloat.hpp"
#include "src/EnemyState/EnemyStateSpecialCharge.hpp"
#include "src/EnemyState/EnemyStateSpecialAttack.hpp"
#include "src/EnemyState/EnemyStateStun.hpp"
#include "src/EnemyState/EnemyStateChoseAttack.hpp"
#include "src/EnemyState/EnemyStateOnDamage.hpp"
#include "src/EnemyState/EnemyStateJumpAttack.hpp"
#include "ObjectAccessor.hpp"

// 敵の生成と初期セットアップ
Enemy::Enemy()
{
	obj_name = "Enemy"; // 名札

	std::ifstream file{ "Enemy.json" };

	enemy_json_data = json::parse(file);

	enemy_is_die = false;

	LoadJson();

	enemy_state_kind = EnemyStateKind::STATE_IDLE;

	// 初期ステートは具体クラスを生成（抽象クラスは生成不可）
	enemy_current_state = std::make_shared<EnemyStateIdle>();

	//インスタンス生成
	enemy_animater = std::make_shared<EnemyAnimater>(obj_modelhandle, enemy_state_kind);

	// ダメージクールタイム設定
	ConfigureDamageCooldown(static_cast<int>(TAKEDAMAGE_COOLDOWN));

}

Enemy::~Enemy() {}

void Enemy::LoadJson()
{
	// 3Dモデル読み込み
	std::string modelPath = enemy_json_data["enemy_model"];
	std::string handnamePath = enemy_json_data["enemy_hand_name"];
	float cuapsuleHeight = enemy_json_data["enemy_capsule_height"];
	float cuapsuleRadius = enemy_json_data["enemy_capsule_radius"];

	COLLISION_CAPSULE_HEIGHT = cuapsuleHeight;  // カプセル判定高さ
	COLLISION_CAPSULE_RADIUS = cuapsuleRadius;  // カプセル判定半径

	obj_modelhandle = MV1LoadModel(modelPath.c_str());
	character_handname = MV1SearchFrame(obj_modelhandle, handnamePath.c_str()); // 右手末端フレームID
	character_hand_position = MV1GetFramePosition(obj_modelhandle, character_handname); // 手先取得
	// 3Dモデルのスケール決定
	MV1SetScale(obj_modelhandle, VGet(ENEMY_SCALE, ENEMY_SCALE, ENEMY_SCALE));
}

// 初期化（位置/HP/状態などを初期状態に戻す）
void Enemy::Initialize()
{
	obj_hp = ENEMY_MAXHP; // HP リセット
	MV1SetMaterialDifColor(obj_modelhandle, 0, Pallet::White_F.GetHandleF());
	enemy_state_kind = EnemyStateKind::STATE_CHOSEATTACK;
	enemy_current_state = std::make_shared<EnemyStateChoseAttack>();

	enemy_is_die = false;

	InitializeStates();
	enemy_current_state->Enter();

	obj_position = VGet(0, 0, ENEMY_INIT_POSITION); // 初期位置
	
	// プレイヤー方向を向く
	obj_direction = VSub(VGet(0,0,0), obj_position);
	float angle = atan2(obj_direction.x, obj_direction.z);
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, angle + DX_PI_F, 0.0f));

	SetPosition();    // モデル座標反映
}

void Enemy::InitializeStates()
{
	states[EnemyStateKind::STATE_IDLE] = std::make_shared<EnemyStateIdle>();						// STATE_IDLE用の具体クラスに差し替え
	states[EnemyStateKind::STATE_CHARGE] = std::make_shared<EnemyStateCharge>();					// STATE_CHARGW用の具体クラスに差し替え
	states[EnemyStateKind::STATE_RUNRIGHT] = std::make_shared<EnemyStateDodge>(obj_position);		// STATE_RUNRIGHT用の具体クラスに差し替え
	states[EnemyStateKind::STATE_RUNLEFT] = std::make_shared<EnemyStateDodge>(obj_position);		// STATE_RUNLEFT用の具体クラスに差し替え
	states[EnemyStateKind::STATE_CHASE] = std::make_shared<EnemyStateChase>(obj_position);			// STATE_CHASE用の具体クラスに差し替え
	states[EnemyStateKind::STATE_FIREATTACK] = std::make_shared<StateFireAttack>();					// STATE_FIREATTACK用の具体クラスに差し替え
	states[EnemyStateKind::STATE_WATERATTACK] = std::make_shared<StateWaterAttack>();				// STATE_WATERATTACK用の具体クラスに差し替え
	states[EnemyStateKind::STATE_WINDATTACK] = std::make_shared<StateWindAttack>();					// STATE_WINDATTACK用の具体クラスに差し替え
	states[EnemyStateKind::STATE_FLOAT] = std::make_shared<EnemyStateFloat>(obj_position);			// STATE_FLOAT用の具体クラスに差し替え
	states[EnemyStateKind::STATE_SPECIAL_CHARGE] = std::make_shared<EnemyStateSpecialCharge>();		// STATE_SPECIAL_CHARGE用の具体クラスに差し替え
	states[EnemyStateKind::STATE_SPECIALATTACK] = std::make_shared<EnemyStateSpecialAttack>();		// STATE_SPECIALATTACK用の具体クラスに差し替え
    states[EnemyStateKind::STATE_STUN] = std::make_shared<EnemyStateStun>();						// STATE_STUN用の具体クラスに差し替え
	states[EnemyStateKind::STATE_CHOSEATTACK] = std::make_shared<EnemyStateChoseAttack>();			// STATE_IDLE用の具体クラスに差し替え
	states[EnemyStateKind::STATE_ONDAMAGE] = std::make_shared<EnemyStateOnDamage>();				// STATE_ONDAMAGE用の具体クラスに差し替え
	states[EnemyStateKind::STATE_JUMPATTACK] = std::make_shared<EnemyStateJumpAttack>(obj_position);// STATE_JUMPATTACK用の具体クラスに差し替え
}

// タイトル更新（アニメのみ）
void Enemy::UpdateTitle()
{
	enemy_state_kind = EnemyStateKind::STATE_SPECIALATTACK;

	enemy_animater->Update();

	if (enemy_animater->GetAnimationFrame() == 0 )
	{
		EffectCreator::GetEffectCreator().PlayReturn(EffectCreator::EffectType::Flame, obj_position);
	}
}

// 毎フレーム更新
void Enemy::Update()
{
	// デバッグ: Jキーで死亡
	if ((CheckHitKey(KEY_INPUT_J) != 0))
	{
		obj_hp = 100;
	}

	UpdateAngle();				// プレイヤーの方向を向く
	UpdateStateAction();		// ステート処理
	enemy_animater->Update();	// 
	CheckMoveRange();			// 行動範囲補正
	SetPosition();				// モデル位置反映
	TickDamageCooldown();		// 無敵進行
}

// ゲームクリア時更新（死亡演出+花火）
void Enemy::UpdateGameClear()
{
	// 一度だけ死亡/花火開始
	if (!enemy_is_die)
	{
		EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::EnemyDeath, obj_position);
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::FireWorks, obj_position);
		enemy_is_die = true;
	}
	else
	{
		// 位置更新
		EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::FireWorks, obj_position);
	}

	enemy_state_kind = EnemyStateKind::STATE_DIE;
	enemy_animater->Update();
}

// ゲームオーバー時更新（ポーズ用）
void Enemy::UpdateGameOver()
{
	if (enemy_state_kind != EnemyStateKind::STATE_IDLE)
	{
		enemy_state_kind = EnemyStateKind::STATE_SPECIALATTACK;
	}
	if (enemy_animater->GetAmimIsEnd())
	{
		enemy_state_kind = EnemyStateKind::STATE_IDLE;
	}
	enemy_animater->Update();
}

void Enemy::UpdateTutorial()
{

	enemy_state_kind = EnemyStateKind::STATE_IDLE;
	
	enemy_animater->Update();
}

// ステート毎の処理
void Enemy::UpdateStateAction()
{
	enemy_state_kind = enemy_current_state->GetNextState();

	if (enemy_current_state != states.at(enemy_state_kind))
	{
		enemy_current_state->Exit();
		enemy_current_state = states.at(enemy_state_kind);
		enemy_current_state->Enter();
	}

	enemy_current_state->Update();
}

// プレイヤー方向を向く
void Enemy::UpdateAngle()
{
	if (enemy_state_kind != EnemyStateKind::STATE_STUN)
	{
		obj_direction = VSub(ObjectAccessor::GetObjectAccessor().GetPlayerPosition(), obj_position);
		float angle = atan2(obj_direction.x, obj_direction.z);
		MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
	}
}

// モデル座標反映
void Enemy::SetPosition()
{
	MV1SetPosition(obj_modelhandle, obj_position);
	character_hand_position = MV1GetFramePosition(obj_modelhandle, character_handname);
}

void Enemy::StopEnemyHandEffect()
{
}

// 描画
void Enemy::Draw()
{

	MV1DrawModel(obj_modelhandle);

	if (ChengeDebugFlag())
	{
		SetLogDrawArea(0, 100, 600, 1000);
		setPrintColorDx(Pallet::LemonYellow.GetHandle());
		printfDx("EnemyState %s\n", EnemyStateToString(enemy_state_kind));
		printfDx("EnemyPosition.x: %f", obj_position.x);
		printfDx(" y %f", obj_position.y);
		printfDx(" z %f\n\n", obj_position.z);
		DrawLine3D(obj_position, VAdd(obj_position, VGet(0, ENEMY_HITEFFECT_HEIGHT, 0)),Pallet::Red.GetHandle());
		DrawCapsule3D(obj_position, VAdd(obj_position, VGet(0, COLLISION_CAPSULE_HEIGHT, 0)), COLLISION_CAPSULE_RADIUS,16, Pallet::Red.GetHandle(), Pallet::Red.GetHandle(),false);
	}
}
