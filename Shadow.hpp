#pragma once
#include "GameObject.hpp"

class Shadow : public GameObject
{
public:
    Shadow();
    ~Shadow();

    void Initialize() override;
    void Update() override;
    void Draw() override ;

    int GetShadowMapHandle() const { return obj_modelhandle; }
    VECTOR GetLightDir()const { return obj_direction; }

private:

    static constexpr int SHADOW_QUALITY = 2048;    // 影のクオリティ
    static constexpr float SHADOW_ANGLESPEED = 0.001f;    // 影のクオリティ

};