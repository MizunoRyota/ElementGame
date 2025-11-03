#include "stdafx.hpp"
#include "Pallet.hpp"
#include "Bullet.hpp"
#include "EffectCreator.hpp" // 追従エフェクト用

Bullet::Bullet()
{
	bullet_isactive = false; // 非アクティブ開始
}

Bullet::~Bullet() {}

void Bullet::Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed, int effectTypeIndex)
{
	// 既存の追従エフェクトを停止
	if (bullet_trail_handle >= 0)
	{
		StopEffekseer3DEffect(bullet_trail_handle);
		bullet_trail_handle = -1;
	}

	bullet_position = pos;
	bullet_rawdirection = VNorm(dir); // 進行基準方向正規化
	bullet_direction = VScale(bullet_rawdirection, speed);
	bullet_speed = speed;
	bullet_life = BULLET_LIFE; // 寿命リセット

	bullet_isHoming = false;
	bullet_homingTime = 0.0f;
	bullet_target_getter = nullptr;
	bullet_effect_type_index = effectTypeIndex; // エフェクト種

	InitializeBulletRadius(effectTypeIndex); // 半径設定
	ChangeActiveTrue(); // 有効化

	// エフェクト再生開始
	if (bullet_effect_type_index >= 0)
	{
		bullet_trail_handle = EffectCreator::GetEffectCreator().PlayReturn(static_cast<EffectCreator::EffectType>(bullet_effect_type_index), bullet_position);
	}
	else
	{
		// fallback to generic trail
		bullet_trail_handle = EffectCreator::GetEffectCreator().PlayReturn(EffectCreator::EffectType::BulletHoming, bullet_position);
	}
}

// 追加: ホーミング版初期化
void Bullet::InitializeHoming(const VECTOR& pos,
	const VECTOR& dir,
	float speed,
	std::function<VECTOR()> targetGetter,
	float homingTime,
	float turnSpeedRad,
	int effectTypeIndex)
{
	Initialize(pos, dir, speed, effectTypeIndex); // 共通初期化
	bullet_isHoming = true;
	bullet_homingTime = homingTime;
	bullet_turnSpeed = turnSpeedRad;
	bullet_target_getter = std::move(targetGetter);

}

void Bullet::InitializeBulletRadius(int effectTypeIndex)
{
	switch (effectTypeIndex)
	{
	case (static_cast<int>(EffectCreator::EffectType::BulletStraight)):
		bullet_radius = BULLET_FIRE_RADIUS; break;
	case (static_cast<int>(EffectCreator::EffectType::BulletDiffusion)):
		bullet_radius = BULLET_DIFFUSION_RADIUS; break;
	case (static_cast<int>(EffectCreator::EffectType::BulletHoming)):
		bullet_radius = BULLET_HOMING_RADIUS; break;
	case (static_cast<int>(EffectCreator::EffectType::BulletSpecial)):
		bullet_radius = BULLET_SPECIAL_RADIUS; break;
	case (static_cast<int>(EffectCreator::EffectType::BulletPlayer)):
		bullet_radius = BULLET_PLAYER_RADIUS; break;
	default: break;
	}
}

void Bullet::Update()
{
	if (!IsActive()) return; // 非アクティブ
	Move(); // 移動
	// 追従エフェクト位置更新
	if (bullet_trail_handle >= 0)
	{
		SetPosPlayingEffekseer3DEffect(bullet_trail_handle, bullet_position.x, bullet_position.y, bullet_position.z);
	}
	StopEffect(); // 寿命/条件終了判定
}

void Bullet::StopEffect()
{
	if (bullet_effect_type_index == static_cast<int>(EffectCreator::EffectType::BulletSpecial))
	{
		if (bullet_position.y <= 0) // 地面到達
		{
			ChangeActiveFalse();
			ResetPosition();
		}
	}
	else if (bullet_life <= 0 || bullet_position.y <= 0)
	{
		ChangeActiveFalse();
		ResetPosition();
	}
}

static VECTOR SlerpDirection(const VECTOR& from, const VECTOR& to, float maxStepRad)
{
	VECTOR a = VNorm(from);
	VECTOR b = VNorm(to);
	float dot = VDot(a, b);
	dot = std::clamp(dot, -1.0f, 1.0f);
	float angle = acosf(dot);
	if (angle < 1e-5f) return b; // ほぼ同方向
	float step = min(maxStepRad, angle);
	float t = step / angle;
	float sinAngle = sinf(angle);
	float coeff0 = sinf((1.0f - t) * angle) / sinAngle;
	float coeff1 = sinf(t * angle) / sinAngle;
	VECTOR out = VAdd(VScale(a, coeff0), VScale(b, coeff1));
	return VNorm(out);
}

void Bullet::Move()
{
	bullet_life -= BULLET_COUNT; // 寿命減算
	// ホーミング処理
	if (bullet_isHoming && bullet_homingTime > 0.0f && bullet_target_getter)
	{
		VECTOR targetPos = bullet_target_getter();
		VECTOR desired = VSub(targetPos, bullet_position);
		if (VSquareSize(desired) > 0.0001f)
		{
			desired = VNorm(desired);
			bullet_rawdirection = SlerpDirection(bullet_rawdirection, desired, bullet_turnSpeed);
		}
		bullet_homingTime -= 1.0f;
		if (bullet_homingTime <= 0.0f) bullet_isHoming = false; // 追尾終了
	}
	// 位置反映
	bullet_direction = VScale(bullet_rawdirection, bullet_speed);
	bullet_position = VAdd(bullet_position, bullet_direction);
}

void Bullet::ChangeActiveFalse()
{
	bullet_isactive = false;
	if (bullet_trail_handle >= 0) // 追従エフェクト停止
	{
		StopEffekseer3DEffect(bullet_trail_handle);
		bullet_trail_handle = -1;
	}
}

void Bullet::ChangeActiveTrue() { bullet_isactive = true; }

void Bullet::ResetPosition()
{
	bullet_position = VGet(0, 0, 0);
}

void Bullet::Draw()
{
	// 可視デバッグが必要なら描画を有効化
	DrawSphere3D(bullet_position, bullet_radius, 10, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);
	  // 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	if (bullet_radius == BULLET_SPECIAL_RADIUS)
	{
		DrawCone3D(VGet(bullet_position.x, SHADOW_TOP_HEIGHT, bullet_position.z), VGet(bullet_position.x, 0, bullet_position.z), bullet_radius, SHADOW_DIV, Pallet::Red.GetHandle(), Pallet::Red.GetHandle(), true);
	}
	else
	{
		DrawCone3D(VGet(bullet_position.x, SHADOW_TOP_HEIGHT, bullet_position.z), VGet(bullet_position.x, 0, bullet_position.z), bullet_radius, SHADOW_DIV, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), true);
	}

	// 描画ブレンドモードをアルファブレンド（５０％）にする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}