#include "stdafx.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "SharedData.hpp"

Scene::Scene(SceneManager& manager, SharedData& sharedData)
    : m_manager{ manager }
    , m_sharedData{ sharedData }  {}

void Scene::Initialize()
{
    // –³ˆ—
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
    m_manager.ChangeScene(name);
}
