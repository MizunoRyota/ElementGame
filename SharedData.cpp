#include "stdafx.hpp"
#include "SharedData.hpp"
#include "Shadow.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Effect.hpp"
#include "Stage.hpp"
#include "Skydome.hpp"
#include "Enemy.hpp"
#include "UiManager.hpp"
#include "UiHpBar.hpp"
#include "UiEnemyHpBar.hpp"

SharedData::SharedData()
{
    stage = std::make_shared<Stage>();
    shadow = std::make_shared<Shadow>();
    input = std::make_shared<Input>();
    camera = std::make_shared<Camera>();
    player = std::make_shared<Player>();
    skydome = std::make_shared<Skydome>();
    enemy = std::make_shared<Enemy>();
    ui = std::make_shared<UiManager>();
    camera->SetPlayer(player);
    enemy->SetPlayer(player);
    player->SetEnemy(enemy);
    player->SetCamera(camera);
    player->SetInput(input);

    // UI—v‘f“o˜^ (ƒvƒŒƒCƒ„[HP / “GHP)
    ui->AddElement(std::make_shared<UiHpBar>(player));
    ui->AddElement(std::make_shared<UiEnemyHpBar>(enemy));

    AddList(skydome);
    AddList(stage);
    AddList(shadow);
    AddList(input);
    AddList(player);
    AddList(enemy);
    AddList(camera);
}

SharedData::~SharedData()
{
}

void SharedData::AddList(std::shared_ptr<GameObject> obj)
{
    objects.push_back(obj);
}

void SharedData::InitializeAll()
{
    for (auto object : objects)
    {
        object->Initialize();
    }
}

void SharedData::UpdateAll()
{
    for (auto object : objects)
    {
        object->Update();
    }
    if (ui) ui->Update(1.0f / 60.0f);
}

void SharedData::DrawAll()
{
    for (auto object : objects)
    {
        object->Draw();
    }
    if (ui) ui->Draw();
}

std::shared_ptr<GameObject> SharedData::FindObject(std::string_view obj_name)
{
    for (auto object : objects)
    {
        if (object->GetNameTag() == obj_name)
        {
            return object;
        }
    }
    return nullptr;
}