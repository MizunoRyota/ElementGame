#include "stdafx.hpp"

#include "SceneManager.hpp"

SceneManager::SceneManager()
    : m_nowScene{ nullptr }
    , m_sharedData{ new SharedData{} } {}

SceneManager::~SceneManager()
{
    delete m_sharedData; m_sharedData = nullptr;

    for (const auto& pair : m_scenes)
    {
        delete pair.second;
    }
}

void SceneManager::Update() const
{
    if (m_nowScene != nullptr)
    {
        m_nowScene->Update();
    }
}

void SceneManager::Draw() const
{
    if (m_nowScene != nullptr)
    {
        m_nowScene->Draw();
    }
}

void SceneManager::ChangeScene(const std::string_view name)
{
#ifdef _DEBUG
    
    try
    {
        m_nowScene = m_scenes.at(name);
        m_nowScene->Initialize();
    }
    catch (...)
    {
        assert(!"存在しないキーが指定されました。");
    }

#else

    m_nowScene = m_scenes[name];
    m_nowScene->Initialize();

#endif
}
