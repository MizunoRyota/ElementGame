#include "stdafx.hpp"
#include "Crystal.hpp"
#include "GameObject.hpp"
#include "Enemy.hpp"
#include "EffectCreator.hpp"

Crystal::Crystal()
{
	std::ifstream file{ "Crystal.json" };

	json data = json::parse(file);

	std::string path = data["crystal_graph"];

	character_hp = CRYSTAL_MAXHP;
	COLLISION_CAPSULE_HEIGHT = 2.5f;  // カプセル判定高さ
	COLLISION_CAPSULE_RADIUS = 2.5f;  // カプセル判定高さ
	obj_modelhandle = MV1LoadModel(path.c_str());
	obj_name = "Crystal";
	MV1SetScale(obj_modelhandle, VGet(CRYSTAL_SCALE, CRYSTAL_SCALE, CRYSTAL_SCALE)); // スケール適用

	// 初期化
	crystal_break = false;
	crystal_init = false;
	crystal_angle = 0.0f;

}

Crystal::~Crystal()
{
}

void Crystal::Initialize()
{

	std::ifstream file{ "Crystal.json" };

	json data = json::parse(file);

	auto arr = data["init_pos"];

	obj_position = VGet(arr[0], arr[1], arr[2]);

	// 初期化
	character_hp = CRYSTAL_MAXHP;
	crystal_break = false;
	crystal_init = false;
	crystal_angle = 0.0f;
}

void Crystal::ChangeActive()
{
	if (enemy_reference->GetEnemyState() != STATE_SPECIAL_CHARGE || crystal_break)
	{
		character_hp = CRYSTAL_MAXHP;
		crystal_break = false;
		crystal_init = false;
		crystal_angle = 0.0f;
		obj_position = VGet(0.0f, -10.0f, 0.0f);
		EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Crystal);
		EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeEnergy);

		return;
	}
	else if (enemy_reference->GetEnemyState() == STATE_SPECIAL_CHARGE && !crystal_init)
	{
		obj_position = VAdd(enemy_reference->GetPosition(), VGet(0.0f, 10.0f, 0.0f));
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::Crystal, obj_position);
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::ChargeEnergy, obj_position);

		crystal_init = true;
		return;
	}
}

void Crystal::ChangeBreak()
{
	crystal_break = true;
	crystal_init = false;
}

void Crystal::Update()
{

	ChangeActive();



	// 敵を中心に円を描くように移動
	if (enemy_reference && enemy_reference->GetEnemyState() == STATE_SPECIAL_CHARGE && crystal_init)
	{
		MoveHorizontal();
	}

	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::Crystal, obj_position);
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::ChargeEnergy, obj_position);
	EffectCreator::GetEffectCreator().SetRotateEffect(EffectCreator::EffectType::ChargeEnergy, enemy_reference->GetPosition());

	MV1SetPosition(obj_modelhandle, obj_position); // 位置適用

}

void Crystal::MoveHorizontal()
{
	// 角度からX,Z位置を計算して、敵を中心に円運動させる
	if (!enemy_reference) return;

	crystal_angle += ROTATION_SPEED;
	if (crystal_angle > DX_TWO_PI) crystal_angle -= DX_TWO_PI;

	float cos = cosf(crystal_angle);
	float sin = sinf(crystal_angle);

	VECTOR center_position = enemy_reference->GetPosition();

	obj_position = VAdd(center_position, VGet(ROTATION_RADIUS * cos,  offset_y, ROTATION_RADIUS * sin));

}

void Crystal::Draw()
{
	if (enemy_reference->GetEnemyState() == STATE_SPECIAL_CHARGE && !crystal_break)
	{
		MV1DrawModel(obj_modelhandle);
	}
}