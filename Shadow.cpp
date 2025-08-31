#include "stdafx.hpp"
#include "Shadow.hpp"

Shadow::Shadow()
{
    obj_name = "Shadow";
    obj_modelhandle = -1;
}

Shadow::~Shadow() {}

void Shadow::Initialize()
{
    obj_modelhandle = MakeShadowMap(SHADOW_QUALITY, SHADOW_QUALITY);

    static float angle = 0.0f; // ラジアン単位での角度
    angle += 0.01f; // 動く速さ（必要に応じて調整）

    // ライトの方向を円運動で更新（半径1の円）
    float radius = 1.0f;
    float x = radius * cosf(angle);
    float y = -1.0f; // 上から照らすイメージ（Y軸は固定）
    float z = radius * sinf(angle);

    obj_direction = VNorm(VGet(x, y, z)); // 正規化して方向ベクトルに

    // シャドウマップが想定するライトの方向もセット
    SetShadowMapLightDirection(obj_modelhandle, obj_direction);
}

void Shadow::Update()
{

    //シャドウを描画する範囲を指定
    //VECTOR minPos = VSub(VGet(50.0f, 50.0f, 50.0f), VGet(50.0f, 50.0f, 50.0f));
    //VECTOR maxPos = VAdd(VGet(50.0f, -0.10f, 50.0f), VGet(50.0f, 25.0f, 50.0f));
    static float angle = 0.0f; // ラジアン単位での角度
    angle += SHADOW_ANGLESPEED; // 動く速さ（必要に応じて調整）

    // ライトの方向を円運動で更新（半径1の円）
    float radius = 1.0f;
    float x = radius * cosf(angle);
    float y = -1.0f; // 上から照らすイメージ（Y軸は固定）
    float z = radius * sinf(angle);

    obj_direction = VNorm(VGet(x, y, z)); // 正規化して方向ベクトルに

    // シャドウマップが想定するライトの方向もセット
    SetShadowMapLightDirection(obj_modelhandle, obj_direction);
    SetShadowMapDrawArea(obj_modelhandle, VGet(-50.0f, -0.10f, -50.0f), VGet(50.0f, 25.0f, 50.0f));

}

void Shadow::Draw()
{
    //処理なし
}