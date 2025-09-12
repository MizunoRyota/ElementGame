#include "stdafx.hpp"
#include "Pallet.hpp"
#include "Bullet.hpp"

Bullet::Bullet()
{
	bullet_isactive = false;
}

Bullet::~Bullet() {}

void Bullet::Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed)
{
	bullet_position = pos;
	bullet_rawdirection = VNorm(dir);
	bullet_direction = VScale(bullet_rawdirection, speed);
	bullet_speed = speed;
	bullet_life = BULLET_LIFE;

	bullet_isHoming = false;
	bullet_homingTime = 0.0f;
	bullet_targetGetter = nullptr;

	ChangeActiveTrue();
}

// 追加: ホーミング版初期化
void Bullet::InitializeHoming(const VECTOR& pos,
	const VECTOR& dir,
	float speed,
	std::function<VECTOR()> targetGetter,
	float homingTime,
	float turnSpeedRad)
{
	Initialize(pos, dir, speed);
	bullet_isHoming = true;
	bullet_homingTime = homingTime;
	bullet_turnSpeed = turnSpeedRad;
	bullet_targetGetter = std::move(targetGetter);
}

void Bullet::Update()
{
	if (!IsActive()) return;

	Move();

	if (bullet_life <= 0)
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

	// ほぼ同方向
	if (angle < 1e-5f) return b;

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
	bullet_life -= BULLET_COUNT;

	// ホーミング中
	if (bullet_isHoming && bullet_homingTime > 0.0f && bullet_targetGetter)
	{
		VECTOR targetPos = bullet_targetGetter();
		VECTOR desired = VSub(targetPos, bullet_position);
		if (VSquareSize(desired) > 0.0001f)
		{
			desired = VNorm(desired);
			bullet_rawdirection = SlerpDirection(bullet_rawdirection, desired, bullet_turnSpeed);
		}

		bullet_homingTime -= 1.0f;
		if (bullet_homingTime <= 0.0f)
		{
			bullet_isHoming = false; // 以後は直進
		}
	}

	// 実際の移動
	bullet_direction = VScale(bullet_rawdirection, bullet_speed);
	bullet_position = VAdd(bullet_position, bullet_direction);
}

void Bullet::ChangeActiveFalse() { bullet_isactive = false; }
void Bullet::ChangeActiveTrue()  { bullet_isactive = true; }

void Bullet::ResetPosition()
{
	bullet_position = VGet(0, 0, 0);
}

void Bullet::Draw()
{
	DrawSphere3D(bullet_position, 0.3f, 20, Pallet::Violet.GetHandle(), Pallet::Violet.GetHandle(), false);
}