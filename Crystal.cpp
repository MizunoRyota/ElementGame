#include "stdafx.hpp"
#include "Crystal.hpp"
#include "GameObject.hpp"
#include "Enemy.hpp"

Crystal::Crystal()
{
	obj_hp = CRYSTAL_MAXHP;
	COLLISION_CAPSULE_HEIGHT = 2.5f;  // カプセル判定高さ
	COLLISION_CAPSULE_RADIUS = 2.5f;  // カプセル判定高さ
	obj_modelhandle = MV1LoadModel("data/3dmodel/Crystal/Crystal.mv1");
	obj_name = "Crystal";
	MV1SetScale(obj_modelhandle, VGet(CRYSTAL_SCALE, CRYSTAL_SCALE, CRYSTAL_SCALE)); // スケール適用

	// 初期化
	crystal_break = false;
	crystal_isinit = false;
	crystal_angle = 0.0f;

}

Crystal::~Crystal()
{
}

void Crystal::Initialize()
{
	// 初期化
	crystal_break = false;
	crystal_isinit = false;
	crystal_angle = 0.0f;
}

void Crystal::ChangeActive()
{
	if (reference_enemy->GetEnemyState() != STATE_SPECIAL_CHARGE)
	{
		obj_position = VGet(0.0f, 0.0f, 0.0f);
		return;
	}
	else if (reference_enemy->GetEnemyState() == STATE_SPECIAL_CHARGE && !crystal_isinit)
	{
		obj_position = VAdd(reference_enemy->GetPosition(), VGet(0.0f, 10.0f, 0.0f));
		crystal_isinit = true;
	}
}

void Crystal::ChangeBreak()
{
	crystal_break = true;
	obj_position = VGet(0.0f, -10.0f, 0.0f);
}

void Crystal::Update()
{

	ChangeActive();

	// 敵を中心に円を描くように移動
	if (reference_enemy && reference_enemy->GetEnemyState() == STATE_SPECIAL_CHARGE && !crystal_isinit)
	{
		MoveHorizontal();
	}

	MV1SetPosition(obj_modelhandle, obj_position); // 位置適用
}

void Crystal::MoveHorizontal()
{
	// 角度からX,Z位置を計算して、敵を中心に円運動させる
	if (!reference_enemy) return;

	crystal_angle += ROTATION_SPEED;
	if (crystal_angle > DX_TWO_PI) crystal_angle -= DX_TWO_PI;

	float cos = cosf(crystal_angle);
	float sin = sinf(crystal_angle);

	VECTOR center_position = reference_enemy->GetPosition();

	obj_position = VAdd(center_position, VGet(ROTATION_RADIUS * cos, offset_y, ROTATION_RADIUS * sin));

}

void Crystal::Draw()
{
	if (reference_enemy->GetEnemyState() == STATE_SPECIAL_CHARGE && !crystal_break)
	{
		MV1DrawModel(obj_modelhandle);
	}
}