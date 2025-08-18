#include"DxLib.h"
#include"tchar.h"
#include"Skydome.hpp"

Skydome::Skydome()
	:pos(VGet(0.0f,0,0.0f))
	,SkydomeHandle(0)
{
	SkydomeHandle = MV1LoadModel(_T("data/3dmodel/skydome/Night/Dome_Y902.pmx"));
	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(SkydomeHandle, pos);
	// 3Dモデルのスケール決定
	MV1SetScale(SkydomeHandle, VGet(Scale, Scale, Scale));
}

Skydome::~Skydome()
{
	MV1DeleteModel(SkydomeHandle);
}

void Skydome::Update()
{
	//スカイドームを回転させる
	pos.y -= 0.0003;
	MV1SetRotationXYZ(SkydomeHandle, VGet(0.0f, pos.y, 0.0f)); 
}

void Skydome::Draw()
{
	MV1DrawModel(SkydomeHandle);
}