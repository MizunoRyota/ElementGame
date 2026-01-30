#include "stdafx.hpp"
#include "Crystal.hpp"
#include "GameObject.hpp"
#include "EffectCreator.hpp"
#include "ObjectAccessor.hpp"
#include "src/Sounds/SoundManager.hpp"

Crystal::Crystal()
{
	std::ifstream file{ "Crystal.json" };

	crystal_json_data = json::parse(file);

	LoadJson();

	obj_hp = CRYSTAL_MAXHP;

	obj_name = "Crystal";

	// 初期化
	crystal_is_break = false;
	crystal_is_active = false;
	crystal_angle = 0.0f;

}

Crystal::~Crystal()
{
	MV1DeleteModel(obj_modelhandle);
}

void Crystal::LoadJson()
{
	std::string path = crystal_json_data["crystal_model"];
	obj_modelhandle = MV1LoadModel(path.c_str());
	MV1SetScale(obj_modelhandle, VGet(CRYSTAL_SCALE, CRYSTAL_SCALE, CRYSTAL_SCALE)); // スケール適用

	auto arr = crystal_json_data["init_pos"];
	obj_position = VGet(arr[0], arr[1], arr[2]);

	float cuapsule_num = crystal_json_data["capsule_num"];
	COLLISION_CAPSULE_HEIGHT = cuapsule_num;  // カプセル判定高さ
	COLLISION_CAPSULE_RADIUS = cuapsule_num;  // カプセル判定半径

}

void Crystal::Initialize()
{
	LoadJson();
	// 初期化
	obj_hp = CRYSTAL_MAXHP;
	crystal_is_break = false;
	crystal_is_active = false;
	crystal_angle = 0.0f;
}

void Crystal::ChangeActive()
{

	if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() != EnemyStateKind::STATE_SPECIAL_CHARGE && crystal_is_active)
	{
		obj_hp = CRYSTAL_MAXHP;
		obj_position = VGet(0.0f, -OFFSET_Y, 0.0f);
		EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Crystal);
		EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeBeam);
		crystal_is_break = false;
		crystal_is_active = false;
	}
	if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIAL_CHARGE && !crystal_is_active)
	{
		obj_position = VAdd(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), VGet(0.0f, OFFSET_Y, 0.0f));
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::Crystal, obj_position);
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::ChargeBeam, obj_position);
		crystal_is_active = true;
	}
}

void Crystal::ChangeBreak()
{
	SoundManager::GetSoundManager().PlayBreakCrystalSe();

	obj_hp = CRYSTAL_MAXHP;
	obj_position = VGet(0.0f, -OFFSET_Y, 0.0f);
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Crystal);
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeBeam);
	crystal_is_break = true;
	crystal_is_active = false;
}

void Crystal::Update()
{

	ChangeActive();

	// 敵を中心に円を描くように移動
	if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIAL_CHARGE && crystal_is_active)
	{
		MoveHorizontal();
	}

	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::Crystal, obj_position);
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::ChargeBeam, obj_position);
	EffectCreator::GetEffectCreator().SetRotateEffect(EffectCreator::EffectType::ChargeBeam, ObjectAccessor::GetObjectAccessor().GetEnemyPosition());

	MV1SetPosition(obj_modelhandle, obj_position); // 位置適用

}

void Crystal::MoveHorizontal()
{

	crystal_angle += ROTATION_SPEED;
	if (crystal_angle > DX_TWO_PI_F) crystal_angle -= DX_TWO_PI_F;

	float cos = cosf(crystal_angle);
	float sin = sinf(crystal_angle);

	VECTOR center_position = ObjectAccessor::GetObjectAccessor().GetEnemyPosition();

	obj_position = VAdd(center_position, VGet(ROTATION_RADIUS * cos, OFFSET_Y, ROTATION_RADIUS * sin));

}

void Crystal::Draw()
{
	if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIAL_CHARGE && !crystal_is_break)
	{
		MV1DrawModel(obj_modelhandle);
	}
}