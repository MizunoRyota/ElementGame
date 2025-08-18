#include "Dxlib.h"
#include "Pallet.hpp"
#include "EffekseerForDXLib.h"
#include "EnemyWindAttack.hpp"

EnemyWindAttack::EnemyWindAttack(int modelhandle)
	:EnemyAttackBase(modelhandle)
	, position(VGet(0, 0, 0))
	, moveVec(VGet(0, 0, 0))
	, isBurstShooting(false)
	, burstShotCount(0)
	,burstTimer(0)
{
	action_isend = false;

	effect_handle = LoadEffekseerEffect("data/effekseer/effekseer/Effect/wind.efkefc", 0.5f);
	for (int i = 0; i < BulletNum; i++)
	{
		bullet_position[i] = VGet(0, 0, 0);
		bullet_startposition[i] = VGet(0, 0, 0);
		bullet_isattack = false;
		isshot[i] = false;
		shot_isout[i] = true;
		windeffect_handle[i] = PlayEffekseer3DEffect(effect_handle);
		SetScalePlayingEffekseer3DEffect(windeffect_handle[i], EffectScale, EffectScale, EffectScale);
		bullet_homing[i] = false;
	}
}

EnemyWindAttack::~EnemyWindAttack()
{
}

void EnemyWindAttack::Initialize()
{
	action_isend = false;

	for (int i = 0; i < BulletNum; i++)
	{
		bullet_position[i] = VGet(0, EffectHight, 0);
		SetPosPlayingEffekseer3DEffect(windeffect_handle[i], bullet_position[i].x, bullet_position[i].y, bullet_position[i].z);
		isshot[i] = false;
		shot_isout[i] = true;
		bullet_isattack = false;
	}
}

VECTOR EnemyWindAttack::Update(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)
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
		UpdateTargetBullet();
	}
	UpdateBullet();
	CheckOutBullet();
	PlayEffect();
	return enemy_position;

}

void EnemyWindAttack::MoveToPlayer()
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

bool EnemyWindAttack::IsAttackRange()
{
	//プレイヤーとEnemyの距離の合計を獲得
	keep_distance = VSub(player_position, enemy_position);

	//ベクトルを2乗
	check_distance = VSquareSize(keep_distance);
	//LengthよりDistanceちいさくなったとき返す
	return check_distance <= (AttackRange * AttackRange);
}

void EnemyWindAttack::PlayEffect()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	if (!effect_isplay)
	{
		StopEffekseer3DEffect(playingEffectHandle);
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

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, enemy_position.x, enemy_position.y, enemy_position.z);

}

void EnemyWindAttack::Attack()
{
	bullet_isattack = true;
	if (!isBurstShooting) {
		isBurstShooting = true;
		burstShotCount = 0;
		burstTimer = 0;

		// 最初の1発を即発射
		FireBullet();
		burstShotCount++;
	}
}

void EnemyWindAttack::FireBullet()
{
	for (int i = 0; i < BulletNum; i++)
	{
		if (!isshot[i])
		{
			VECTOR target_position = VAdd(player_position, bullet_position[i]);
			VECTOR dir = VNorm(VSub(target_position, bullet_position[i]));

			//float angleOffset = (rand() % 20 - 10) * DX_PI_F / 180.0f; // 
			//VECTOR right = VCross(dir, VGet(0, 1, 0));  // 横方向
			//dir = VNorm(VAdd(dir, VScale(right, tanf(angleOffset))));

			moveVecs[i] = dir;
			//bullet_position[i] = enemy_position;
			bullet_startposition[i] = bullet_position[i];
			isshot[i] = true;
			shot_isout[i] = false;
			bullet_homing[i] = true; // 最初は追尾ON

			SetPosPlayingEffekseer3DEffect(
				windeffect_handle[i],
				bullet_position[i].x, bullet_position[i].y, bullet_position[i].z
			);
			break;
		}
	}
}

void EnemyWindAttack::UpdateBullet()
{
	for (int i = 0; i < BulletNum; i++)
	{
		if (!isshot[i] && shot_isout[i])
		{
			angle_vector = VGet(0, 0, 0);
			prevbullet_angle[i] = angle_vector;
			bullet_position[i] = MV1GetFramePosition(model_handle, flame_name);
		}
	}
}

void EnemyWindAttack::UpdateTargetBullet()
{
	if (isBurstShooting)
	{
		burstTimer++;

		if (burstTimer >= BurstInterval && burstShotCount < 3)
		{
			burstTimer = 0;
			FireBullet();
			burstShotCount++;
		}

		if (burstShotCount >= 2)
		{
			isBurstShooting = false;
		}
	}

	// --- 弾の移動処理 ---
	for (int i = 0; i < BulletNum; i++)
	{
		if (isshot[i] && !shot_isout[i])
		{
			float bullet_range = VSize(VSub(bullet_position[i], bullet_startposition[i]));

			// 追尾する距離を超えたら追尾終了
			if (bullet_range >= HomingDistance) {
				bullet_homing[i] = false;
			}

			if (bullet_homing[i]) {
				// 追尾中 → プレイヤー方向に少しずつ補正
				VECTOR toPlayer = VNorm(VSub(player_position, bullet_position[i]));
				moveVecs[i] = VNorm(VAdd(moveVecs[i], VScale(toPlayer, 0.05f)));
			}

			// 移動（追尾OFFなら直進）
			bullet_position[i] = VAdd(bullet_position[i], VScale(moveVecs[i], BulletMoveSpeed));

			SetPosPlayingEffekseer3DEffect(
				windeffect_handle[i],
				bullet_position[i].x, bullet_position[i].y, bullet_position[i].z
			);
		}
	}
}

void EnemyWindAttack::CheckOutBullet()
{
	for (int i = 0; i < BulletNum; i++)
	{
		float bullet_range = VSize(VSub(bullet_position[i], bullet_startposition[i]));
		if (bullet_range > BulletRange || bullet_range < -BulletRange)
		{
			isshot[i] = false;
			shot_isout[i] = true;
			bullet_isattack = false;

			action_isend = true;

		}
	}
	// 3発撃ち切っていて、なおかつ「すべての弾が消滅している」なら終了
	if (burstShotCount >= 3)
	{
		bool allOut = true;
		for (int i = 0; i < BulletNum; i++)
		{
			if (isshot[i])  // まだ飛んでいる弾がある
			{
				allOut = false;
				break;
			}
		}

		if (allOut)
		{
			action_isend = true;
		}
	}
}

void EnemyWindAttack::DebugDraw()
{
	for (int i = 0; i < BulletNum; i++)
	{
		DrawSphere3D(bullet_position[i], 0.6f, 20, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);
	}
}

bool EnemyWindAttack::GetIsAction()
{
	return action_isend;
}
