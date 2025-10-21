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

Enemy::Enemy()
{
	COLLISION_CAPSULE_RADIUS = 0.45f;   // カプセル半径(モデル合わせ & 衝突判定用)
	COLLISION_CAPSULE_HEIGHT = 2.75f;   // カプセル高さ(プレイヤー等との整合)
	enemy_isdie = false;
	enemy_attacktype = 0; // 次攻撃ステート種別初期
	enemy_dodgechose = 0;
	enemy_handname = 0;
	enemy_isaction = false;
	enemy_ischase = false;


	obj_name = "Enemy"; // 識別名
	obj_modelhandle = MV1LoadModel("data/3dmodel/Enemy/Monster.mv1"); // モデル読み込み
	character_handname = MV1SearchFrame(obj_modelhandle, "mixamorig:RightHandMiddle1"); // 手ボーンID


	enemy_state = STATE_CHARGE; // 初期ステート
	MV1SetScale(obj_modelhandle, VGet(ENEMY_SCALE, ENEMY_SCALE, ENEMY_SCALE)); // スケール適用

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
	attack_kind = { STATE_FIREATTACK,STATE_WATERATTACK,STATE_WINDATTACK }; // ランダム候補

	std::random_device rd; // 以下ランダム初期化
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, attack_kind.size() - 1);

	enemy_state = STATE_CHARGE; // 初期ステート

	enemy_isaction = false; // 動作未完了

	enemy_ischase = false; // 追跡中フラグ初期
	
	enemy_isdie = false;
	
	obj_position = VGet(0, 0, 20.0f); // 初期位置

	obj_direction = VGet(0, 0, 1.0f); // 初期位置

	obj_hp = ENEMY_MAXHP; // HP リセット

	// エフェクト再生フラグ初期化
	enemy_groundattack_charge_played = false;
	
	// プレイヤー方向ベクトル
	obj_direction = VSub(VGet(0,0,0), obj_position);
	// 角度算出(Yaw)
	float angle = atan2(obj_direction.x, obj_direction.z);
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, angle + DX_PI_F, 0.0f)); // モデル向き反映

	StopHandEffect(); // 初期化時に手エフェクト停止

	SetPosition();
}

void Enemy::UpdateTitle()
{

	enemy_state = STATE_IDLE;

	enemy_animater->Update(); // アニメ更新

}

void Enemy::Update()
{
	if ((CheckHitKey(KEY_INPUT_J) != 0))
	{
		obj_hp = 0;
	}

	enemy_animater->Update(); // アニメ更新
	UpdateAngle(); // 向き更新
	UpdateStateAction(); // ステート毎挙動
	UpdateHandEffect(); // ハンドエフェクト管理
	enemy_bullet->FireUpdate(); // 弾クール
	CheckMoveRange(); // 範囲補正
	SetPosition(); // モデル座標適用
	TickDamageCooldown(); // 無敵タイマー
}

void Enemy::UpdateGameClear()
{
	StopHandEffect();
	// 一度だけ死亡/打ち上げ演出開始
	if (!enemy_isdie)
	{
		EffectCreator::GetEffectCreator().Play(EffectCreator::EffectType::EnemyDeath, obj_position);      // 単発（死亡演出）
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::FireWorks, obj_position); // ループ(花火)
		//ec.PlayLoop(EffectCreator::EffectType::FireWorks, obj_position); 
		enemy_isdie = true;
	}
	else
	{
		// 位置が変わる可能性があるなら追従（静止なら不要）
		EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::FireWorks, obj_position);
	}

	enemy_state = STATE_DIE;
	enemy_animater->Update(); // アニメ更新
}

void Enemy::UpdateGameOver()
{
	enemy_state = STATE_SPECIALATTACK;
	enemy_animater->Update(); // アニメ更新
}

// 攻撃種に応じたエフェクト種マッピング
EffectCreator::EffectType Enemy::MapEffectTypeForAttack(int attackState) const
{
	switch (attackState)
	{
	case STATE_FIREATTACK: return EffectCreator::EffectType::BulletStraight; // 炎

	case STATE_WATERATTACK: return EffectCreator::EffectType::BulletDiffusion; // 水

	case STATE_WINDATTACK: return EffectCreator::EffectType::BulletHoming; // 風

	default: return EffectCreator::EffectType::BulletSpecial; // 必殺技

	}
}

void Enemy::StartHandEffectForAttack()
{
	// 既に同じ攻撃種のエフェクトが出ているなら何もしない
	if (enemy_hand_effect_handle >= 0 && enemy_hand_effect_attack_state == enemy_attacktype) return;

	// 既存を止める
	StopHandEffect();

	// 手位置取得
	VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
	// 少し上 or 任意オフセットを加味
	handPos = VAdd(handPos, VGet(0, 0.0f, 0));

	const auto effType = MapEffectTypeForAttack(enemy_attacktype);
	enemy_hand_effect_handle = EffectCreator::GetEffectCreator().PlayReturn(effType, handPos);
	enemy_hand_effect_attack_state = enemy_attacktype;
}

void Enemy::StopHandEffect()
{
	if (enemy_hand_effect_handle >= 0)
	{
		// Effekseer 側で個別停止 API が無いため寿命放置でも良い。
		// 必要なら StopEffekseer3DEffect(enemy_hand_effect_handle); を呼ぶが
		// ここでは明示停止は行わずハンドル無効化のみ。
		StopEffekseer3DEffect(enemy_hand_effect_handle);
		enemy_hand_effect_handle = -1;
		enemy_hand_effect_attack_state = -1;
	}
}

void Enemy::UpdateStateAction()
{
	switch (enemy_state)
	{
	case STATE_IDLE:
		obj_position = enemy_move->MoveToOrigin(obj_position); // 原点へ戻る
		break;

	case STATE_CHARGE:
		// GROUNDATTACK から離脱した場合リセット
		if (enemy_groundattack_charge_played && enemy_state != STATE_SPECIAL_CHARGE)
		{
			enemy_groundattack_charge_played = false;
		}
		if (enemy_isaction = enemy_animater->GetAmimIsEnd()) // アニメ終了→次行動決定
		{
			enemy_dodgechose = GetRand(1); // 回避方向乱数

			ChoseAttackType(); // 攻撃種選択
			// 攻撃種決定直後に手エフェクト生成
			StartHandEffectForAttack();

			if (enemy_dodgechose == 0)      enemy_state = STATE_RUNLEFT;
			
			else if (enemy_dodgechose == 1) enemy_state = STATE_RUNRIGHT;
		}
		break;

	case STATE_RUNLEFT:
		obj_position = enemy_dodge->DodgeEnemy(obj_position, obj_direction, enemy_state);
		if (enemy_dodge->GetIsDodgeEnd()) enemy_state = STATE_CHASE; // 回避完了→追跡
		break;

	case STATE_RUNRIGHT:
		obj_position = enemy_dodge->DodgeEnemy(obj_position, obj_direction, enemy_state);
		if (enemy_dodge->GetIsDodgeEnd()) enemy_state = STATE_CHASE;
		break;

	case STATE_CHASE:
		obj_position = enemy_move->MoveToTarget(obj_position, player_reference->GetPosition()); // 追従
		if (enemy_ischase = enemy_chase->RangeWithin(obj_position, player_reference->GetPosition()))
		{
			enemy_state = static_cast<EnemyState>(enemy_attacktype); // 攻撃へ
		}
		break;

	case STATE_FIREATTACK:
		if (enemy_animater->GetAmimFrame() == FIREATTACK_TIMING)
		{
			VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
			handPos = VAdd(handPos, VGet(0, BULLET_HIGHT, 0));
			enemy_bullet->FireStraight(handPos, obj_direction, FIREBULLET_SPEED);
		}
		if (enemy_isaction = enemy_animater->GetAmimIsEnd()) { enemy_state = STATE_CHARGE; StopHandEffect(); }
		break;

	case STATE_WATERATTACK:
		if (enemy_animater->GetAmimFrame() == WATERATTACK_TIMING)
		{
			VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
			handPos = VAdd(handPos, VGet(0, BULLET_HIGHT, 0));
			enemy_bullet->FireDiffusion(handPos, obj_direction, WATERBULLET_SPEED);
		}
		if (enemy_isaction = enemy_animater->GetAmimIsEnd()) { enemy_state = STATE_CHARGE; StopHandEffect(); }
		break;

	case STATE_WINDATTACK:
		if (enemy_animater->GetAmimFrame() >= WINDATTACK_TIMING)
		{
			VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
			enemy_bullet->FireHoming(handPos, obj_direction, WINDBULLET_SPEED, player_reference);
		}
		if (enemy_isaction = enemy_animater->GetAmimIsEnd()) { enemy_state = STATE_CHARGE; StopHandEffect(); }
		break;

	case STATE_WALKBACK:
		// TODO: 実装予定
		break;

	case STATE_FLOAT:
		obj_position = enemy_move->MoveToOrigin(obj_position); // float 中は中央へ
		if (enemy_move->GetIsOrigin()) enemy_state = STATE_SPECIAL_CHARGE;
		break;

	case STATE_SPECIAL_CHARGE:
		// チャージエフェクトを再生
		if (!enemy_groundattack_charge_played)
		{
			enemy_specialattack->Initialize();
			EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::Barrior, obj_position); // ループ(花火)
			EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::EnemyCharge, obj_position);
			
			enemy_groundattack_charge_played = true;
		}
		
		enemy_specialattack->UpdateChrgeCount();

		if (obj_hp <= ENEMY_FHASE_FIVE) enemy_state = STATE_ONDAMAGE; // HP 低下遷移

		if (enemy_isaction = !enemy_specialattack->GetIsCharge())
		{
			enemy_state = STATE_SPECIALATTACK; // 終了→特殊
			EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Barrior); // ループ(花火)
			EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::EnemyCharge); // ループ(花火)

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
		if (enemy_isaction = enemy_animater->GetAmimIsEnd())
		{
			enemy_state = STATE_CHARGE;
			enemy_attacktype = 0;
			StopHandEffect();
		}
		break;

	case STATE_ONDAMAGE:
		if (enemy_isaction = enemy_animater->GetAmimIsEnd()) { enemy_state = STATE_CHARGE; StopHandEffect(); }
		break;

	default:
		break;
	}
}

void Enemy::ChoseAttackType()
{
	if (attack_kind.empty()) return; // 念のため安全策

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, static_cast<int>(attack_kind.size()) - 1);

	if (obj_hp >= ENEMY_FHASE_ONE)
	{
		// 旧: enemy_attacktype = attack_kind[STATE_FIREATTACK]; // OOB の原因
		enemy_attacktype = STATE_FIREATTACK; // 直接設定
	}
	else if (obj_hp >= ENEMY_FHASE_TWO)
	{
		enemy_attacktype = attack_kind[dist(gen)];
	}
	else if (obj_hp >= ENEMY_FHASE_THREE)
	{
		enemy_attacktype = attack_kind[dist(gen)];
	}
	else if (obj_hp >= ENEMY_FHASE_FOUR && !enemy_specialattack->GetIsCharge())
	{
		enemy_attacktype = STATE_FLOAT;
	}
	else if (!enemy_specialattack->GetIsActive())
	{
		enemy_attacktype = attack_kind[dist(gen)];
	}
}

void Enemy::UpdateHandEffect()
{
	// 手エフェクトを追従させる
	if (enemy_hand_effect_handle >= 0)
	{
		VECTOR handPos = MV1GetFramePosition(obj_modelhandle, character_handname);
		SetPosPlayingEffekseer3DEffect(enemy_hand_effect_handle, handPos.x, handPos.y, handPos.z);
	}
}

void Enemy::UpdateAngle()
{
	// プレイヤー方向ベクトル
	obj_direction = VSub(player_reference->GetPosition(), obj_position);
	// 角度算出(Yaw)
	float angle = atan2(obj_direction.x, obj_direction.z);
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, angle + DX_PI_F, 0.0f)); // モデル向き反映
}

void Enemy::SetPosition()
{
	MV1SetPosition(obj_modelhandle, obj_position); // 位置適用
}

void Enemy::Draw()
{
	MV1DrawModel(obj_modelhandle); // 描画
}