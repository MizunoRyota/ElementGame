#include "stdafx.hpp"
#include "Crystal.hpp"
#include "GameObject.hpp"
#include "EffectCreator.hpp"
#include "ObjectAccessor.hpp"
#include "src/Sounds/SoundManager.hpp"

Crystal::Crystal()
{
	std::ifstream file{ "Crystal.json" };

	json data = json::parse(file);

	std::string path = data["crystal_graph"];

	obj_hp = CRYSTAL_MAXHP;

	COLLISION_CAPSULE_HEIGHT = 2.5f;  // カプセル判定高さ
	COLLISION_CAPSULE_RADIUS = 2.5f;  // カプセル判定高さ

	obj_modelhandle = MV1LoadModel(path.c_str());
	obj_name = "Crystal";
	MV1SetScale(obj_modelhandle, VGet(CRYSTAL_SCALE, CRYSTAL_SCALE, CRYSTAL_SCALE)); // スケール適用

	// 初期化
	crystal_is_break = false;
	crystal_is_init = false;
	crystal_angle = 0.0f;

}

Crystal::~Crystal()
{
	MV1DeleteModel(obj_modelhandle);
}

void Crystal::Initialize()
{

	std::ifstream file{ "Crystal.json" };

	json data = json::parse(file);

	auto arr = data["init_pos"];

	obj_position = VGet(arr[0], arr[1], arr[2]);

	// 初期化
	obj_hp = CRYSTAL_MAXHP;
	crystal_is_break = false;
	crystal_is_init = false;
	crystal_angle = 0.0f;
}

void Crystal::ChangeActive()
{

	if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() != EnemyStateKind::STATE_SPECIAL_CHARGE && crystal_is_init)
	{
		obj_hp = CRYSTAL_MAXHP;
		crystal_angle = 0.0f;
		obj_position = VGet(0.0f, -10.0f, 0.0f);
		EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Crystal);
		EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeBeam);
		crystal_is_break = false;
		crystal_is_init = false;

	}
	if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIAL_CHARGE && !crystal_is_init)
	{
		obj_position = VAdd(ObjectAccessor::GetObjectAccessor().GetEnemyPosition(), VGet(0.0f, OFFSET_Y, 0.0f));
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::Crystal, obj_position);
		EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::ChargeBeam, obj_position);

		crystal_is_init = true;
		return;
	}
}

void Crystal::ChangeBreak()
{
	SoundManager::GetSoundManager().PlayBreakCrystalSe();

	obj_hp = CRYSTAL_MAXHP;
	crystal_angle = 0.0f;
	obj_position = VGet(0.0f, -10.0f, 0.0f);
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::Crystal);
	EffectCreator::GetEffectCreator().StopLoop(EffectCreator::EffectType::ChargeBeam);
	crystal_is_break = true;
	crystal_is_init = false;

}

void Crystal::Update()
{

	ChangeActive();

	// 敵を中心に円を描くように移動
	if (ObjectAccessor::GetObjectAccessor().GetEnemyStateKind() == EnemyStateKind::STATE_SPECIAL_CHARGE && crystal_is_init)
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
	if (crystal_angle > DX_TWO_PI) crystal_angle -= DX_TWO_PI;

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