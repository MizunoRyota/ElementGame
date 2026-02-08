#include "stdafx.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "SharedData.hpp"
#include "src/Sounds/SoundManager.hpp"
Scene::Scene(SceneManager& manager, SharedData& sharedData)
    : m_manager{ manager }
    , m_sharedData{ sharedData }
    ,scene_out_is_end(false)
    {}

void Scene::Initialize()
{
    // 無処理
}

void Scene::WhiteOut()
{
    if (scene_out_is_end == true)
    {
        alpha = 0;
        scene_out_is_end = false;
    }
    while (alpha < WHITEOUT_TIME)
    {

        alpha += SCENE_OUT_TIMESPEED;

        DrawCircle(0, SCREEN_HEIGHT, alpha, Pallet::SpringGreen.GetHandle(), true);
        DrawCircle(SCREEN_WIDTH, 0, alpha, Pallet::Violet.GetHandle(), true);
        DrawCircle(SCREEN_WIDTH, SCREEN_HEIGHT, alpha, Pallet::DeepSkyBlue.GetHandle(), true);
        DrawCircle(0, 0, alpha, Pallet::Red.GetHandle(), true);


        // 画面を更新
        ScreenFlip();
    }

    scene_out_is_end = true;
}

void Scene::ReturnScene()
{
    while (alpha > 0)
    {
        ClearDrawScreen();

        alpha -= SCENE_OUT_TIMESPEED;

        DrawCircle(0, SCREEN_HEIGHT, alpha, Pallet::SpringGreen.GetHandle(), true);
        DrawCircle(SCREEN_WIDTH, 0, alpha, Pallet::Violet.GetHandle(), true);
        DrawCircle(SCREEN_WIDTH, SCREEN_HEIGHT, alpha, Pallet::DeepSkyBlue.GetHandle(), true);
        DrawCircle(0, 0, alpha, Pallet::Red.GetHandle(), true);


        // 画面を更新
        ScreenFlip();
    }
}

void Scene::Update()
{
    // 無処理
}

void Scene::Draw() 
{
    // 無処理
}

void Scene::ChangeScene(const std::string_view name)
{
    WhiteOut();
    ReturnScene();
    if (scene_out_is_end)
    {
        m_manager.ChangeScene(name);
    }
}
