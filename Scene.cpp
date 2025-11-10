#include "stdafx.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "SharedData.hpp"

Scene::Scene(SceneManager& manager, SharedData& sharedData)
    : m_manager{ manager }
    , m_sharedData{ sharedData }
    ,whiteout_is_end(false)
    {}

void Scene::Initialize()
{
    // ñ≥èàóù
}

void Scene::WhiteOut()
{
    if (whiteout_is_end == true)
    {
        alpha = 0;
        whiteout_is_end = false;
    }
    while (alpha < WHITEOUT_TIME)
    {

        alpha += WHITEOUT_TIMESPEED;

        // âÊñ ÇîíêFÇ≈ìhÇËÇ¬Ç‘Ç∑
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha * WHITEOUT_TIMESPEED));
        DrawCircle(0, SCREEN_HEIGHT, alpha, Pallet::SpringGreen.GetHandle(), true);
        DrawCircle(SCREEN_WIDTH, 0, alpha, Pallet::Violet.GetHandle(), true);
        DrawCircle(SCREEN_WIDTH, SCREEN_HEIGHT, alpha, Pallet::DeepSkyBlue.GetHandle(), true);
        DrawCircle(0, 0, alpha, Pallet::Red.GetHandle(), true);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        // âÊñ ÇçXêV
        ScreenFlip();
    }

    whiteout_is_end = true;
}

void Scene::Update()
{
    // ñ≥èàóù
}

void Scene::Draw() 
{
    // ñ≥èàóù
}

void Scene::ChangeScene(const std::string_view name)
{
    WhiteOut();

    if (whiteout_is_end)
    {
        m_manager.ChangeScene(name);
    }
}
