#include "stdafx.hpp"
#include "tchar.h"
#include "Skydome.hpp"
#include "GameObject.hpp"

Skydome::Skydome()
	:skydome_position(VGet(0.0f,0,0.0f))
	, skydome_modelhandle(0)
{
	obj_name = "Skydome";
	skydome_position = VGet(0.0f, 0, 0.0f);
	skydome_modelhandle = 0;
	skydome_modelhandle = MV1LoadModel(_T("data/3dmodel/skydome/Sunny/Dome_X502.pmx"));
	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(skydome_modelhandle, skydome_position);
	// 3Dモデルのスケール決定
	MV1SetScale(skydome_modelhandle, VGet(SCALE, SCALE, SCALE));
}

Skydome::~Skydome()
{
	MV1DeleteModel(skydome_modelhandle);
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
	skydome_position.y -= MOVESPEED;
	MV1SetRotationXYZ(skydome_modelhandle, VGet(0.0f, skydome_position.y, 0.0f));
}

/// <summary>
/// 描画
/// </summary>
void Skydome::Draw()
{
	MV1DrawModel(skydome_modelhandle);
}