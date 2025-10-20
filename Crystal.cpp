#include "stdafx.hpp"
#include "Crystal.hpp"
#include "GameObject.hpp"
#include "Enemy.hpp"
Crystal::Crystal()
{
	obj_modelhandle = MV1LoadModel("data/3dmodel/Crystal/Crystal.mv1");
	obj_name = "Crystal";
	MV1SetScale(obj_modelhandle, VGet(CRYSTAL_SCALE, CRYSTAL_SCALE, CRYSTAL_SCALE)); // スケール適用
}

Crystal::~Crystal()
{
}

void Crystal::Update()
{
	if (reference_enemy->GetEnemyState() != STATE_SPECIAL_CHARGE) { return; }
	else if (reference_enemy->GetEnemyState() == STATE_SPECIAL_CHARGE)
	{
		obj_position = VAdd(reference_enemy->GetPosition(),VGet(0.0f,10.0f,0.0f));
	}
	MV1SetPosition(obj_modelhandle, obj_position); // 位置適用

}

void Crystal::Draw()
{
	if (reference_enemy->GetEnemyState() == STATE_SPECIAL_CHARGE)
	{
		MV1DrawModel(obj_modelhandle);
	}
}