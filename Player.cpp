#include "stdafx.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "BulletFire.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "PlayerMove.hpp"
#include "PlayerAnimater.hpp"

// プレイヤー生成と初期セットアップ
Player::Player()
{
	obj_name = "Player"; // 名前識別

	// 3Dモデル読み込み
	obj_modelhandle = MV1LoadModel(_T("data/3dmodel/Player/Player.mv1"));
	
	character_handname  = MV1SearchFrame(obj_modelhandle, "f_middle.03.R"); // 右手末端フレームID
	// モデルスケール適用
	MV1SetScale(obj_modelhandle, VGet(SCALE, SCALE, SCALE));
	 COLLISION_CAPSULE_RADIUS = 0.06f; // カプセル判定半径
	 COLLISION_CAPSULE_HEIGHT = 2.5f;  // カプセル判定高さ
	obj_position = VGet(0, 0, 0); // 初期位置
	obj_direction = VGet(0, 0, 0); // 向き(未使用初期化)

	player_animater = std::make_shared<PlayerAnimater>(obj_modelhandle,player_state); // アニメーション制御
	player_move = std::make_shared<PlayerMove>(); // 移動制御
	player_bullet = std::make_shared<BulletFire>(); // 弾発射

	player_state = STATE_HANDIDLE; // 初期ステート

	character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname); // 手先取得

	// 手元ループエフェクト
	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::HandEffect, character_handposition);
	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::HandCharge, character_handposition);
	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::Laser, character_handposition);

	// 被弾後クール(30f)設定
	ConfigureDamageCooldown(1);
}

Player::~Player() {}

// 初期化（位置/向き/モデル姿勢などを初期状態に）
void Player::Initialize()
{
	obj_hp = PLAYER_MAXHP; // HP リセット
	obj_position = VGet(0, 0, 0);
	obj_direction = VGet(0, 0, 0);
	// モデル回転初期
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoveAngle() + DX_PI_F, 0.0f));
	// モデル座標適用
	MV1SetPosition(obj_modelhandle, obj_position);
}

// 毎フレーム更新
void Player::Update()
{

	// デバッグ: Kキーで強制死亡
	if ((CheckHitKey(KEY_INPUT_K) != 0))
	{
		obj_hp = 0;
	}

	player_bullet->FireUpdate(); // 弾クール更新

	player_move->Update(input_reference, camera_reference); // 入力→移動量計算

	Move(); // 位置反映

	UpdateStateAction(); // 攻撃入力/ステート決定

	UpdateHandEffect(); // 手元エフェクト位置更新

	player_animater->Update(); // アニメーション更新

	// 無敵タイマー減算
	TickDamageCooldown();
}

// 手元ループエフェクトの位置更新
void Player::UpdateHandEffect()
{
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::HandEffect, character_handposition);
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::HandCharge, character_handposition);
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::Laser, character_handposition);
	EffectCreator::GetEffectCreator().SetRotateEffect(EffectCreator::EffectType::Laser, camera_reference->GetCameraDir());
}

// 攻撃入力に応じてステートを切替え、弾を発射
void Player::UpdateStateAction()
{

	character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname); // 手先取得

	if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		player_state = STATE_ATTACK; // 攻撃ステート
		// 手先位置 + 視線方向へオフセットして弾を発射
		player_bullet->FirePlayer(VAdd(character_handposition, VScale(camera_reference->GetCameraDir(), BULLETFIRE_DISTANCE)), camera_reference->GetCameraDir(), BULLET_SPEED);
	}
	else
	{
		player_state = STATE_HANDIDLE; // 待機
	}
}

// 入力で得た移動量を反映し、モデル姿勢/位置を適用
void Player::Move()
{
	// 入力で得た移動量反映
	obj_position = VAdd(obj_position, player_move->GetMoveScale());
	character_handposition = MV1GetFramePosition(obj_modelhandle, character_handname); // 手先取得

	CheckMoveRange(); // 範囲外補正
	// 当たり判定での補正などを入れる場合はここ

	// プレイヤーの回転
	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, player_move->GetMoveAngle() + DX_PI_F, 0.0f));
	// プレイヤーモデルの配置
	MV1SetPosition(obj_modelhandle, obj_position);
}

// 描画
void Player::Draw()
{
	MV1DrawModel(obj_modelhandle); // 3D描画
}