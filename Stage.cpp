#include "stdafx.hpp"
#include "Stage.hpp"
#include "EffectCreator.hpp" 
Stage::Stage()
{
	obj_name = "Stage";
	obj_direction = VGet(0, 0, 0);
	obj_position = VGet(0, STAGE_HIGHT, 0);
	obj_modelhandle = 0;
	obj_effecthandle = -1;
	obj_modelhandle = MV1LoadModel(_T("data/3dmodel/Stage/Stage5.mv1"));
	// 3Dモデルのスケール決定
	MV1SetScale(obj_modelhandle, VGet(SCALE, SCALE, SCALE));
	MV1SetPosition(obj_modelhandle, obj_position);

}

Stage::~Stage()
{
}

/// <summary>
/// 初期化
/// </summary>
void Stage::Initialize()
{
	obj_direction = VGet(0, 0, 0);
	obj_position = VGet(0, 0, 0);

	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::FireGround, obj_position); // ループ(花火)

}

/// <summary>
/// 更新
/// </summary>
void Stage::Update()
{
	EffectCreator::GetEffectCreator().PlayLoop(EffectCreator::EffectType::FireGround, obj_position); // ループ(花火)

	// 位置が変わる可能性があるなら追従（静止なら不要）
	EffectCreator::GetEffectCreator().SetLoopPosition(EffectCreator::EffectType::FireGround, VAdd(obj_position, VGet(0, 0.1f, 0)));
}

/// <summary>
/// 描画
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(obj_modelhandle);
}