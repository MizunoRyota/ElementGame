#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Pallet.hpp"
#include "EnemyWaterAttack.hpp"

EnemyWaterAttack::EnemyWaterAttack(int modelhandle)
	:EnemyAttackBase(modelhandle)
	, position(VGet(0, 0, 0))
	, moveVec(VGet(0, 0, 0))
{
	action_isend = false;

	effect_handle = LoadEffekseerEffect("data/effekseer/effekseer/Effect/water.efkefc", 0.5f);
	for (int i = 0; i < BulletNum; i++)
	{
		bullet_position[i] = VGet(0, 0, 0);
		bullet_startposition[i] = VGet(0, 0, 0);
		bullet_isattack = false;
		isshot[i] = false;
		shot_isout[i] = true;
		watereffect_handle[i] = PlayEffekseer3DEffect(effect_handle);
		SetScalePlayingEffekseer3DEffect(watereffect_handle[i], EffectScale, EffectScale, EffectScale);
	}
}
/// <summary>
/// 
/// </summary>
EnemyWaterAttack::~EnemyWaterAttack()
{}

void EnemyWaterAttack::Initialize()
{
	action_isend = false;

	for (int i = 0; i < BulletNum; i++)
	{
		bullet_position[i] = VGet(0, EffectHight, 0);
		SetPosPlayingEffekseer3DEffect(watereffect_handle[i], bullet_position[i].x, bullet_position[i].y, bullet_position[i].z);
		isshot[i] = false;
		shot_isout[i] = true;
		bullet_isattack = false;
	}
}

/// @brief 
/// 更新
/// @param playerpos 
/// @param enemypos 
/// @return 
VECTOR EnemyWaterAttack::Update(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)
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

void EnemyWaterAttack::MoveToPlayer()
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

bool EnemyWaterAttack::IsAttackRange()
{
	//プレイヤーとEnemyの距離の合計を獲得
	keep_distance = VSub(player_position, enemy_position);

	//ベクトルを2乗
	check_distance = VSquareSize(keep_distance);
	//LengthよりDistanceちいさくなったとき返す
	return check_distance <= (AttackRange * AttackRange);
}

void EnemyWaterAttack::PlayEffect()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
   for (int i = 0; i < BulletNum; i++)
    {
        if (!effect_isplay)
        {
            StopEffekseer3DEffect(watereffect_handle[i]);
            watereffect_handle[i] = PlayEffekseer3DEffect(effect_handle);
            SetScalePlayingEffekseer3DEffect(watereffect_handle[i], EffectScale, EffectScale, EffectScale);

            //エフェクトを再生する
            effect_isplay = true;
            effect_isend = false;
        }
        else
        {
            time += PlayEffectSpeed;
            if (time >= EndTime) // 30フレーム経過したらエフェクトを終了
            {
                effect_isend = true;
                effect_isplay = false;
                time = 0; // 時間をリセット
            }
        }
        SetPosPlayingEffekseer3DEffect(watereffect_handle[i], bullet_position[i].x, bullet_position[i].y, bullet_position[i].z);
    }
}

void EnemyWaterAttack::Attack()
{

	bullet_isattack = true;

	// カメラの向き（前方ベクトル）
	VECTOR forward = angle_vector; // 仮：カメラの前方を返す関数を想定
	forward = VNorm(forward); // 正規化

	// 放射状の角度差（ラジアン）
	constexpr float angleOffset = DX_PI_F / 6.0f; // 約10度

	// 発射する3方向ベクトルを作る
	VECTOR directions[BulletNum];
	directions[0] = forward; // 中央

	// 左右方向のベクトルを作る（Y軸を基準に回転）
	MATRIX rotLeft = MGetRotY(-angleOffset);
	MATRIX rotRight = MGetRotY(angleOffset);

	directions[1] = VTransform(forward, rotLeft);  // 左
	directions[2] = VTransform(forward, rotRight); // 右

	// 3発撃つ
	for (int j = 0; j < BulletNum; j++)
	{
		for (int i = 0; i < BulletNum; i++)
		{
			if (!isshot[i]) // 空いてる弾スロットを使う
			{
				bullet_position[i] = MV1GetFramePosition(model_handle, flame_name);
				bullet_startposition[i] = bullet_position[i];
				prevbullet_angle[i] = directions[j];
				isshot[i] = true;
				shot_isout[i] = false;
				break;
			}
		}
	}

}

void EnemyWaterAttack::UpdateBullet()
{
	for (int i = 0; i < BulletNum; i++)
	{
		if (!isshot[i] && shot_isout[i])
		{
			angle_vector = VGet(0, 0, 0);
			angle_vector = VNorm(angle_vector);
			prevbullet_angle[i] = angle_vector;
			bullet_position[i] = MV1GetFramePosition(model_handle, flame_name);
		}
		if (isshot[i] && shot_isout[i])
		{
			shot_isout[i] = false;
		}
		if (!shot_isout[i] && isshot[i])
		{
			angle_vector = prevbullet_angle[i];
			angle_vector = VScale(angle_vector, BulletMoveSpeed);
			bullet_position[i] = VAdd(bullet_position[i], angle_vector);
		}
	}
}

void EnemyWaterAttack::DebugDraw()
{
	for (int i = 0; i < BulletNum; i++)
	{
		DrawSphere3D(bullet_position[i], 0.6f, 20, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);
	}
}

void EnemyWaterAttack::CheckOutBullet()
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
}

bool EnemyWaterAttack::GetIsAction()
{
	return action_isend;
}