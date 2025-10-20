#include "stdafx.hpp"
#include "SharedData.hpp"
#include "EffectCreator.hpp"
#include "Shadow.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Stage.hpp"
#include "Skydome.hpp"
#include "Enemy.hpp"
#include "UiManager.hpp"
#include "UiHpBar.hpp"
#include "UiEnemyHpBar.hpp"
#include "GameTimer.hpp"
#include "DarkFilm.hpp"
#include "reticle.hpp"
#include "UiDashBar.hpp"
#include "Text.hpp"
#include "TakeDamageUi.hpp"
#include "BulletCreator.hpp"
#include "SceneGraph.hpp"
#include "Crystal.hpp"


SharedData::SharedData()
{

    stage = std::make_shared<Stage>();
    shadow = std::make_shared<Shadow>();
    input = std::make_shared<Input>();
    camera = std::make_shared<Camera>();
    player = std::make_shared<Player>();
    skydome = std::make_shared<Skydome>();
    enemy = std::make_shared<Enemy>();
    crystal = std::make_shared<Crystal>();
    ui = std::make_shared<UiManager>();

    //参照渡し
    camera->SetPlayer(player);
    camera->SetEnemy(enemy);
    enemy->SetPlayer(player);
    crystal->SetEnemy(enemy);
    player->SetEnemy(enemy);
    player->SetCamera(camera);
    player->SetInput(input);

    // UI要素登録 (プレイヤーHP / 敵HP)
    ui->AddElement(std::make_shared<DarkFilm>(enemy));      // 暗転を追加
    ui->AddElement(std::make_shared<UiHpBar>(player));      // プレイヤーのHPバー
    ui->AddElement(std::make_shared<UiEnemyHpBar>(enemy));  // エネミーのHPバー
    ui->AddElement(std::make_shared<GameTimer>());          // ゲームタイマー追加
    ui->AddElement(std::make_shared<UiDashBar>(player));    // ゲームタイマー追加
    ui->AddElement(std::make_shared<TakeDamageUi>(player));    // ゲームタイマー追加
    ui->AddElement(std::make_shared<Reticle>());            // レティクル
    ui->AddElement(std::make_shared<Text>());
    ui->AddElement(std::make_shared<SceneGraph>());

    //ゲームオブジェクト登録
    AddGameList(skydome);
    AddGameList(stage);
    AddGameList(shadow);
    AddGameList(input);
    AddGameList(player);
    AddGameList(enemy);
    AddGameList(camera);
    AddGameList(crystal);


    //影を写すオブジェクト登録
    AddShadowReady(player);
    AddShadowReady(enemy);

}

SharedData::~SharedData()
{
}

void SharedData::AddTitleList(std::shared_ptr<GameObject> obj)
{
    objects_title.push_back(obj);
}

void SharedData::AddGameList(std::shared_ptr<GameObject> obj)
{
    objects_game.push_back(obj);
}

void SharedData::AddGameClearList(std::shared_ptr<GameObject> obj)
{
    objects_gameclear.push_back(obj);
}

void SharedData::AddGameOverList(std::shared_ptr<GameObject> obj)
{
    objects_gameover.push_back(obj);

}
void SharedData::AddShadowReady(std::shared_ptr<GameObject> obj)
{
    objects_shadow_ready.push_back(obj);
}

void SharedData::InitializeAll()
{
    EffectCreator::GetEffectCreator().Initialize();
    for (auto object : objects_game)
    {
        object->Initialize();
    }
    BulletCreator::GetBulletCreator().Initialize();
}

void SharedData::UpdateTitle()
{
    for (auto object : objects_game)
    {
        object->UpdateTitle();
    }
    if (ui) ui->UpdateTitle();
}

void SharedData::UpdateTutorial()
{
    for (auto object : objects_game)
    {
        object->UpdateTitle();
    }
    if (ui) ui->UpdateTutorial();
}

void SharedData::UpdateGame()
{
    for (auto object : objects_game)
    {
        object->Update();
    }
    if (ui) ui->Update();
    EffectCreator::GetEffectCreator().Update();

}

void SharedData::UpdateGameClear()
{
    for (auto object : objects_game)
    {
        object->UpdateGameClear();
    }
    if (ui) ui->UpdateGameClear();
}

void SharedData::UpdateGameOver()
{
    for (auto object : objects_game)
    {
        object->UpdateGameOver();
    }
    if (ui) ui->UpdateGameOver();
}

void SharedData::DrawShadowReady()
{
    for (auto object : objects_shadow_ready)
    {
        object->Draw();
    }
}

void SharedData::DrawTitle()
{
    for (auto object : objects_game)
    {
        object->Draw();
    }
    if (ui) ui->DrawTitle();
}

void SharedData::DrawTutorial()
{
    for (auto object : objects_game)
    {
        object->Draw();
    }
    if (ui) ui->DrawTutorial();
}

void SharedData::DrawAll()
{
    for (auto object : objects_game)
    {
        object->Draw();
    }
    if (ui) ui->Draw();
    // 置き換え: 直接DrawEffekseer3D()ではなく、マネージャ描画
    EffectCreator::GetEffectCreator().Draw();
}

void SharedData::DrawGameClear()
{
    for (auto object : objects_game)
    {
        object->Draw();
    }
    if (ui) ui->DrawGameClear();
    // 置き換え: 直接DrawEffekseer3D()ではなく、マネージャ描画
    EffectCreator::GetEffectCreator().Draw();
}

void SharedData::DrawGameOver()
{
    for (auto object : objects_gameover)
    {
        object->DrawGameOver();
    }
    // 置き換え: 直接DrawEffekseer3D()ではなく、マネージャ描画
    EffectCreator::GetEffectCreator().Draw();
    if (ui) ui->DrawGameOver();
}

std::shared_ptr<GameObject> SharedData::FindObject(std::string_view obj_name)
{
    for (auto object : objects_game)
    {
        if (object->GetNameTag() == obj_name)
        {
            return object;
        }
    }
    return nullptr;
}