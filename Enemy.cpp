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
#include "EffectCreator.hpp"
#include "Palsy.hpp"

// 敵の生成と初期セットアップ
Enemy::Enemy()
{
	COLLISION_CAPSULE_RADIUS = 0.45f;   // カプセル判定半径(モデルに合わせる)
	COLLISION_CAPSULE_HEIGHT = 2.75f;   // カプセル判定高さ
	enemy_is_die = false;
	enemy_attacktype = 0;   // 攻撃ステートの初期値
	enemy_dodgechose = 0;
	enemy_handname = 0;
	enemy_is_action = false;
	enemy_is_chase = false;
	enemy_is_palsy = false;
	obj_name = "Enemy"; // 名札
	obj_modelhandle = MV1LoadModel("data/3dmodel/Enemy/monster2.mv1"); // モデル読み込み
	character_handname = MV1SearchFrame(obj_modelhandle, "mixamorig:RightHandMiddle1"); // 右手ボーンID

	enemy_state = STATE_CHARGE; // 初期ステート
	MV1SetScale(obj_modelhandle, VGet(ENEMY_SCALE, ENEMY_SCALE, ENEMY_SCALE)); // スケール

	enemy_animater = std::make_shared<EnemyAnimater>(obj_modelhandle, enemy_state);
	enemy_bullet = std::make_shared<BulletFire>();
	enemy_dodge = std::make_shared<Dodge>();
	enemy_specialattack = std::make_shared<SpecialAttack>();
	enemy_move = std::make_shared<EnemyMove>();
	enemy_palsy = std::make_shared <Palsy>();
	// ダメージクールタイム設定
	ConfigureDamageCooldown(static_cast<int>(TAKEDAMAGE_COOLDOWN));
}

Enemy::~Enemy() {}

// 初期化（位置/HP/状態などを初期状態に戻す）
void Enemy::Initialize()
{
	attack_kind = { STATE_FIREATTACK,STATE_WATERATTACK,STATE_WINDATTACK }; // 攻撃候補

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, attack_kind.size() - 1);

	enemy_state = STATE_CHARGE;
	enemy_is_action = false;
	enemy_is_chase = false;
	enemy_is_die = false;
	
	obj_position = VGet(0, 0, 20.0f); // 初期位置
	obj_direction = VGet(0, 0, 1.0f); // 初期向き
	character_hp = ENEMY_MAXHP; // HP リセット

	// エフェクト関連フラグ
	enemy_special_charge_playerd = false;
	
	// プレイヤー方向を向く
	obj_direction = VSub(VGet(0,0,0), obj_position);
	float angle = atan2(obj_direction.x, obj_direction.z);
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, angle + DX_PI_F, 0.0f));

	StopHandEffect(); // 開始時は手エフェクトなし
	SetPosition();    // モデル座標反映
}

// タイトル更新（アニメのみ）
void Enemy::UpdateTitle()
{
	enemy_state = STATE_IDLE;
	enemy_animater->Update();
}

// 毎フレーム更新
void Enemy::Update()
{
	// デバッグ: Jキーで死亡
	if ((CheckHitKey(KEY_INPUT_J) != 0))
	{
		character_hp = 0;
	}

	UpdateAngle();        // プレイヤーの方向を向く
	UpdateStateAction();  // ステート処理
	enemy_animater->Update();
	UpdateHandEffect();   // 手エフェクト追従
	enemy_bullet->FireUpdate(); // 弾クール
	CheckMoveRange();     // 行動範囲補正
	SetPosition();        // モデル位置反映
	TickDamageCooldown(); // 無敵進行
}

// ゲームクリア時更新（死亡演出+花火）
void Enemy::UpdateGameClear()
{
	StopHandEffect();
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

	enemy_state = STATE_DIE;
	enemy_animater->Update();
}

// ゲームオーバー時更新（ポーズ用）
void Enemy::UpdateGameOver()
{
	enemy_state = STATE_SPECIALATTACK;
	enemy_animater->Update();
}

// 攻撃ステート -> エフェクト種別へマッピング
EffectCreator::EffectType Enemy::MapEffectTypeForAttack(int attackState) const
{
	switch (attackState)
	{
	case STATE_FIREATTACK: return EffectCreator::EffectType::BulletStraight; // 火
	case STATE_WATERATTACK: return EffectCreator::EffectType::BulletDiffusion; // 水
	case STATE_WINDATTACK: return EffectCreator::EffectType::BulletHoming; // 風
	default: return EffectCreator::EffectType::BulletSpecial; // 特殊
	}
}

// 手エフェクトを攻撃に応じて再生
void Enemy::StartHandEffectForAttack()
{
	// 既に同攻撃のエフェクトが再生中なら何もしない
	if (enemy_hand_effect_handle >= 0 && enemy_hand_effect_attack_state == enemy_attacktype) return;

	// いったん停止
	StopHandEffect();

	// 手の現在位置
	VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
	handPos = VAdd(handPos, VGet(0, 0.0f, 0));

	const auto effType = MapEffectTypeForAttack(enemy_attacktype);
	enemy_hand_effect_handle = EffectCreator::GetEffectCreator().PlayReturn(effType, handPos);
	enemy_hand_effect_attack_state = enemy_attacktype;
}

// 手エフェクト停止
void Enemy::StopHandEffect()
{
	if (enemy_hand_effect_handle >= 0)
	{
		StopEffekseer3DEffect(enemy_hand_effect_handle);
		enemy_hand_effect_handle = -1;
		enemy_hand_effect_attack_state = -1;
	}
}

// 麻痺ステートに遷移（ループを停止）
void Enemy::ChangeStatePalsy()
{
	enemy_state = STATE_PALSY;
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Barrior);
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EnemyCharge);
}

// ステート毎の処理
void Enemy::UpdateStateAction()
{
	switch (enemy_state)
	{
	case STATE_PALSY:
		enemy_palsy->Update();
		if (!enemy_is_palsy)
		{
			EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::EnemyTire, VAdd(obj_position, VGet(0, GetCapsuleHeight(), 0)));
			enemy_is_palsy = true;
		}
		else if (!enemy_palsy->GetIsPalsy())
		{
			EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EnemyTire);
			enemy_state = STATE_CHARGE;
		}
		break;

	case STATE_IDLE:
		obj_position = enemy_move->MoveToOrigin(obj_position);
		break;

	case STATE_CHARGE:
		// チャージ演出が残っている場合はフラグを戻す
		if (enemy_special_charge_playerd && enemy_state != STATE_SPECIAL_CHARGE)
		{
			enemy_special_charge_playerd = false;
		}
		// アニメ終了で攻撃を選択
		if (enemy_is_action = enemy_animater->GetAmimIsEnd())
		{
			enemy_dodgechose = GetRand(1);
			ChoseAttackType();
			StartHandEffectForAttack();
			if (enemy_dodgechose == 0)      enemy_state = STATE_RUNLEFT;
			else if (enemy_dodgechose == 1) enemy_state = STATE_RUNRIGHT;
		}
		break;

	case STATE_RUNLEFT:
		obj_position = enemy_dodge->DodgeEnemy(obj_position, obj_direction, enemy_state);
		if (enemy_dodge->GetIsDodgeEnd()) enemy_state = STATE_CHASE;
		break;

	case STATE_RUNRIGHT:
		obj_position = enemy_dodge->DodgeEnemy(obj_position, obj_direction, enemy_state);
		if (enemy_dodge->GetIsDodgeEnd()) enemy_state = STATE_CHASE;
		break;

	case STATE_CHASE:
		obj_position = enemy_move->MoveToTarget(obj_position, player_reference->GetPosition());
		if (enemy_is_chase = enemy_chase->RangeWithin(obj_position, player_reference->GetPosition()))
		{
			VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
			EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::ReadyAttack, handPos);
			enemy_state = static_cast<EnemyState>(enemy_attacktype);
		}
		break;

	case STATE_FIREATTACK:

		if (enemy_animater->GetAmimFrame() == FIREATTACK_TIMING)
		{
			VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
			handPos = VAdd(handPos, VGet(0, BULLET_HIGHT, 0));
			enemy_bullet->FireStraight(handPos, obj_direction, FIREBULLET_SPEED);
		}
		if (enemy_is_action = enemy_animater->GetAmimIsEnd()) { enemy_state = STATE_CHARGE; StopHandEffect(); }
		break;

	case STATE_WATERATTACK:

		if (enemy_animater->GetAmimFrame() == WATERATTACK_TIMING)
		{
			VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
			handPos = VAdd(handPos, VGet(0, BULLET_HIGHT, 0));
			enemy_bullet->FireDiffusion(handPos, obj_direction, WATERBULLET_SPEED);
		}
		if (enemy_is_action = enemy_animater->GetAmimIsEnd()) { enemy_state = STATE_CHARGE; StopHandEffect(); }
		break;

	case STATE_WINDATTACK:
		if (enemy_animater->GetAmimFrame() >= WINDATTACK_TIMING)
		{

			VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
			enemy_bullet->FireHoming(handPos, obj_direction, WINDBULLET_SPEED, player_reference);
		}
		if (enemy_is_action = enemy_animater->GetAmimIsEnd()) { enemy_state = STATE_CHARGE; StopHandEffect(); }
		break;

	case STATE_WALKBACK:
		// TODO: 実装
		break;

	case STATE_FLOAT:
		obj_position = enemy_move->MoveToOrigin(obj_position);
		if (enemy_move->GetIsOrigin()) enemy_state = STATE_SPECIAL_CHARGE;
		break;

	case STATE_SPECIAL_CHARGE:
		// チャージ演出開始
		if (!enemy_special_charge_playerd)
		{
			enemy_specialattack->Initialize();
			EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::Barrior, obj_position);
			EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::EnemyCharge, obj_position);
			enemy_special_charge_playerd = true;
		}

		enemy_specialattack->UpdateChrgeCount();

		if (character_hp <= ENEMY_FHASE_FIVE) enemy_state = STATE_ONDAMAGE;

		if (enemy_is_action = !enemy_specialattack->GetIsCharge())
		{
			enemy_state = STATE_SPECIALATTACK; // 発動
			EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Barrior);
			EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EnemyCharge);
		}
		break;

	case STATE_SPECIALATTACK:
		if (enemy_animater->GetAmimFrame() == SPECIALEATTACK_TIMING)
		{
			EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::Roar, obj_position);
			VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
			handPos = VAdd(handPos, VGet(0, BULLET_HIGHT, 0));
			enemy_bullet->FireSpecialAttack(handPos, obj_direction, SPECIALBULLET_SPEED);
		}
		if (enemy_is_action = enemy_animater->GetAmimIsEnd())
		{
			enemy_state = STATE_CHARGE;
			enemy_attacktype = 0;
			StopHandEffect();
		}
		break;

	case STATE_ONDAMAGE:
		if (enemy_is_action = enemy_animater->GetAmimIsEnd()) { enemy_state = STATE_CHARGE; StopHandEffect(); }
		break;

	default:
		break;
	}
}

// 攻撃タイプの決定（HPやチャージ状況で分岐）
void Enemy::ChoseAttackType()
{
	if (attack_kind.empty()) return; // 念のため

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, static_cast<int>(attack_kind.size()) - 1);

	if (character_hp >= ENEMY_FHASE_ONE)
	{
		enemy_attacktype = STATE_FIREATTACK; // 固定
	}
	else if (character_hp >= ENEMY_FHASE_TWO)
	{
		enemy_attacktype = attack_kind[dist(gen)];
	}
	else if (character_hp >= ENEMY_FHASE_THREE)
	{
		enemy_attacktype = attack_kind[dist(gen)];
	}
	else if (character_hp >= ENEMY_FHASE_FOUR && !enemy_specialattack->GetIsCharge())
	{
		enemy_attacktype = STATE_FLOAT;
	}
	else if (!enemy_specialattack->GetIsActive())
	{
		enemy_attacktype = attack_kind[dist(gen)];
	}
}

// 手エフェクトの追従
void Enemy::UpdateHandEffect()
{
	if (enemy_hand_effect_handle >= 0)
	{
		VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
		SetPosPlayingEffekseer3DEffect(enemy_hand_effect_handle, handPos.x, handPos.y, handPos.z);
	}
}

// プレイヤー方向を向く
void Enemy::UpdateAngle()
{
	if (enemy_state != STATE_PALSY)
	{
		obj_direction = VSub(player_reference->GetPosition(), obj_position);
		float angle = atan2(obj_direction.x, obj_direction.z);
		MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
	}
}

// モデル座標反映
void Enemy::SetPosition()
{
	MV1SetPosition(obj_modelhandle, obj_position);
}

// 描画
void Enemy::Draw()
{
	MV1DrawModel(obj_modelhandle);
}