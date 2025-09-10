#include "stdafx.hpp"
#include "Stage.hpp"
#include "Effect.hpp"

Stage::Stage()
{
	obj_name = "Stage";
	obj_direction = VGet(0, 0, 0);
	obj_position = VGet(0, STAGE_HIGHT, 0);
	obj_modelhandle = 0;
	obj_effecthandle = -1;
	obj_modelhandle = MV1LoadModel(_T("data/3dmodel/Stage/Stage3.mv1"));
	obj_effecthandle = LoadEffekseerEffect(_T("data/effekseer/effekseer/Effect/GroundFire.efkefc", 4.5));
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
	obj_direction = VGet(0, 0, 0);
}
/// <summary>
/// 更新
/// </summary>
void Stage::Update()
{
	//処理なし
}

/// <summary>
/// 描画
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(obj_modelhandle);
}