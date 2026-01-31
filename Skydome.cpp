#include "stdafx.hpp"
#include "tchar.h"
#include "Skydome.hpp"
#include "GameObject.hpp"

Skydome::Skydome()
{
	obj_name = "Skydome";
	obj_direction = VGet(0.0f, 0.0f, 0.0f);
	obj_position = VGet(0.0f, 0.0f, 0.0f);
	sunny_direction = 0;
	cloud_direction = 0;
	cloud_modelhandle = MV1LoadModel(_T("data/3dmodel/skydome/Cloud/Dome_EE402.pmx"));
	obj_modelhandle = MV1LoadModel(_T("data/3dmodel/skydome/Sunny/Dome_X502.mv1"));

	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(obj_modelhandle, obj_direction);
	MV1SetPosition(cloud_modelhandle, obj_direction);

	// 3Dモデルのスケール決定
	MV1SetScale(obj_modelhandle, VGet(SCALE, SCALE, SCALE));
	MV1SetScale(cloud_modelhandle, VGet(SCALE, SCALE, SCALE));

}

Skydome::~Skydome()
{
	MV1DeleteModel(obj_modelhandle);
	MV1DeleteModel(cloud_modelhandle);
}

/// <summary>
/// 初期化
/// </summary>
void Skydome::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void Skydome::Update()
{
	//スカイドームを回転させる
	sunny_direction -= SUNNY_MOVESPEED;
	cloud_direction -= CLOUD_MOVESPEED;

	MV1SetRotationXYZ(obj_modelhandle, VGet(0.0f, sunny_direction, 0.0f));
	MV1SetRotationXYZ(cloud_modelhandle, VGet(0.0f, cloud_direction, 0.0f));

}

/// <summary>
/// 描画
/// </summary>
void Skydome::Draw()
{
	MV1DrawModel(obj_modelhandle);
	MV1DrawModel(cloud_modelhandle);
}