#include "stdafx.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "SharedData.hpp"

Scene::Scene(SceneManager& manager, SharedData& sharedData)
    : m_manager{ manager }
    , m_sharedData{ sharedData }
    ,whiteout_isend(false)
    {}

void Scene::Initialize()
{
    // –³ˆ—
}

void Scene::WhiteOut()
{
    int startTime = GetNowCount();
    int endTime = startTime + WHITEOUT_TIME;
    if (whiteout_isend == true)
    {
        whiteout_isend = false;
    }
    while (GetNowCount() < endTime)
    {
        int elapsedTime = GetNowCount() - startTime;
        float alpha = static_cast<float>(elapsedTime) / WHITEOUT_TIME;

        // ‰æ–Ê‚ğ”’F‚Å“h‚è‚Â‚Ô‚·
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha * WHITEOUT_TIMESPEED));
        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Pallet::White.GetHandle(), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        // ‰æ–Ê‚ğXV
        ScreenFlip();
    }
    whiteout_isend = true;
}

void Scene::Update()
{
    // –³ˆ—
}

void Scene::Draw() 
{
    // –³ˆ—
}

void Scene::ChangeScene(const std::string_view name)
{
    WhiteOut();

    if (whiteout_isend)
    {
        m_manager.ChangeScene(name);
    }
}
