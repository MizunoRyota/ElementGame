#include "Dxlib.h"
#include "Pallet.hpp"
#include "EffekseerForDXLib.h"
#include "EnemyFireAttack.hpp"

EnemyFireAttack::EnemyFireAttack(int modelhandle)
	:EnemyAttackBase(modelhandle)
	, position(VGet(0, 0, 0))
	, moveVec(VGet(0, 0, 0))
{
	action_isend = false;
	bullet_isattack = false;
	shot_isout = true;
	isshot = false;
	bullet_position = VGet(0, 0, 0);
	bullet_startposition = (VGet(0, 0, 0));
	effect_handle = LoadEffekseerEffect("data/effekseer/effekseer/Effect/fire.efkefc", 0.5f);
	effect_firehandle = PlayEffekseer3DEffect(effect_handle);
}

EnemyFireAttack::~EnemyFireAttack()
{
}

void EnemyFireAttack::Initialize()
{
	action_isend = false;
	bullet_position = VGet(0, EffectHight, 0);
	SetPosPlayingEffekseer3DEffect(effect_firehandle, bullet_position.x, bullet_position.y, bullet_position.z);
	isshot = false;
	shot_isout = true;
	bullet_isattack = false;
}

VECTOR EnemyFireAttack::Update(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)
{

	this->player_position = playerpos;
	this->enemy_position = enemypos;
	this->angle_vector = angle;
	if (!IsAttackRange() && !bullet_isattack)
	{
		MoveToPlayer();
	}
	else
	{
		Attack();
	}
	UpdateBullet();
	CheckOutBullet();

	PlayEffect();
	return enemy_position;
}

bool EnemyFireAttack::IsAttackRange()
{
	//プレイヤーとEnemyの距離の合計を獲得
	keep_distance = VSub(player_position, enemy_position);

	//ベクトルを2乗
	check_distance = VSquareSize(keep_distance);
	//LengthよりDistanceちいさくなったとき返す
	return check_distance <= (AttackRange * AttackRange);
}

void EnemyFireAttack::MoveToPlayer()
{
	moveVec = VGet(0, 0, 0);

	// プレイヤーと敵の位置ベクトルの差分
	toTarget = VSub(player_position, enemy_position);

	// プレイヤーに向かって進む方向を単位ベクトルで求める
	check_direction = VNorm(toTarget);

	// 敵が進む距離（移動速度に基づく）
	moveVec = VScale(check_direction, MoveSpeed);

	// 敵の位置を更新
	enemy_position = VAdd(enemy_position, moveVec);
}

void EnemyFireAttack::Attack()
{
	if (!bullet_isattack) // 撃ってなければ撃つ
	{
		isshot = true;
		bullet_isattack = true;
		bullet_startposition = bullet_position;
		// プレイヤー方向ベクトル
		VECTOR dir = VNorm(VSub(player_position, enemy_position));

		// 弾の進行方向（スピードを掛ける）
		moveVec = VScale(dir, BulletMoveSpeed);

	}
}

void EnemyFireAttack::UpdateBullet()
{
	if (!isshot && shot_isout)
	{
		angle_vector = VGet(0, 0, 0);
		angle_vector = VNorm(angle_vector);
		prevbullet_angle = angle_vector;
		bullet_position = MV1GetFramePosition(model_handle, flame_name);
	}
	if (bullet_isattack)
	{
		// 移動
		bullet_position = VAdd(bullet_position, moveVec);
	}
}

void EnemyFireAttack::PlayEffect()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	if (!effect_isplay)
	{
		StopEffekseer3DEffect(effect_firehandle);
		//エフェクトを再生する
		effect_isplay = true;
		effect_isend = false;
	}
	else
	{
		effect_playtime += PlayEffectSpeed;
		if (effect_playtime >= EndTime) // 30フレーム経過したらエフェクトを終了
		{
			effect_isend = true;
			effect_isplay = false;
			effect_playtime = 0; // 時間をリセット
		}
	}

	SetPosPlayingEffekseer3DEffect(effect_firehandle, bullet_position.x, bullet_position.y, bullet_position.z);

}

void EnemyFireAttack::CheckOutBullet()
{
	float bullet_range = VSize(VSub(bullet_position, bullet_startposition));
	if (bullet_range > BulletRange || bullet_range < -BulletRange)
	{
		// 移動
		isshot = false;
		shot_isout = true;
		bullet_isattack = false;
		action_isend = true;
		// エフェクトを弾に追従
		SetPosPlayingEffekseer3DEffect(effect_firehandle,bullet_position.x, bullet_position.y, bullet_position.z);
	}
}

bool EnemyFireAttack::GetIsAction()
{
	return action_isend;
}

void EnemyFireAttack::DebugDraw()
{
	DrawSphere3D(bullet_position, 0.6f, 20, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);

}