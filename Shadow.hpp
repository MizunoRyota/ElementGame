#pragma once
#include "GameObject.hpp"

class Shadow : public GameObject
{
public:
    Shadow();
    ~Shadow();

    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override ;          //描画

    int GetShadowMapHandle() const { return obj_modelhandle; }  //影のハンドルを返す
    VECTOR GetLightDir()const { return obj_direction; }         //ライトの方向を返す

private:

    static constexpr int SHADOW_QUALITY = 2048;           // 影のクオリティ
    static constexpr float SHADOW_ANGLESPEED = 0.001f;    // 影のクオリティ

};