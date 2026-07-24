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
#include "reticle.hpp"
#include "UiDashBar.hpp"
#include "Text.hpp"
#include "TakeDamageUi.hpp"
#include "BulletCreator.hpp"
#include "SceneGraph.hpp"
#include "Crystal.hpp"
#include "ObjectAccessor.hpp"
#include "FightOverlayUi.hpp"
#include "CountdownOverlayUi.hpp"

SharedData::SharedData()
{

    // --- ゲーム全体で共有する主要インスタンス作成 ---
    // ここで生成したインスタンスは、
    // - `objects_game` に登録されるものはシーン更新/描画の対象
    // - `ObjectAccessor` に登録されるものは他クラスが取得して利用
    // という二系統で参照される
    stage = std::make_shared<Stage>();
    shadow = std::make_shared<Shadow>();
    input = std::make_shared<Input>();
    crystal = std::make_shared<Crystal>();
    camera = std::make_shared<Camera>();
    player = std::make_shared<Player>();
    skydome = std::make_shared<Skydome>();
    enemy = std::make_shared<Enemy>();
    ui = std::make_shared<UiManager>();

    // --- 共有アクセサへ登録（各所から参照できるようにする） ---
    ObjectAccessor::GetObjectAccessor().SetPlayer(player);
    ObjectAccessor::GetObjectAccessor().SetEnemy(enemy);
    ObjectAccessor::GetObjectAccessor().SetInput(input);
    ObjectAccessor::GetObjectAccessor().SetCamera(camera);
    ObjectAccessor::GetObjectAccessor().SetCrystal(crystal);

    // --- UI要素登録 ---
    // UiManager が保持し、シーンごとの Update/Draw で描画する
    ui->AddElement(std::make_shared<UiHpBar>(player));       // プレイヤーのHPバー
    ui->AddElement(std::make_shared<UiEnemyHpBar>(enemy));   // エネミーのHPバー
    ui->AddElement(std::make_shared<GameTimer>());           // ゲームタイマー
    ui->AddElement(std::make_shared<UiDashBar>(player));     // ダッシュゲージ
    ui->AddElement(std::make_shared<TakeDamageUi>(player));  // 被弾表示
    ui->AddElement(std::make_shared<Reticle>());             // レティクル
    ui->AddElement(std::make_shared<Text>());                // 汎用テキスト
    ui->AddElement(std::make_shared<SceneGraph>());          // デバッグ/情報表示など
    ui->AddElement(std::make_shared<CountdownOverlayUi>());  // カウントダウン演出
    ui->AddElement(std::make_shared<FightOverlayUi>());      // Fight演出

    // --- ゲームオブジェクト登録 ---
    // ※現状 AddTitleList / AddGameList などは同一リストに push_back される実装
    //   （シーンごとの振り分けは Update*/Draw* 呼び出し側で行う）
    AddGameList(skydome);
    AddGameList(stage);
    AddGameList(shadow);
    AddGameList(input);
    AddGameList(crystal);
    AddGameList(player);
    AddGameList(enemy);
    AddGameList(camera);

    // --- 影を写すオブジェクト登録 ---
    // 影描画時に `objects_shadow_ready` を描画する想定
    AddShadowReady(player);
    AddShadowReady(enemy);

}

SharedData::~SharedData()
{
}

void SharedData::AddGameList(std::shared_ptr<GameObject> obj)
{
    // Game用オブジェクト追加
    objects_game.push_back(obj);
}

void SharedData::AddShadowReady(std::shared_ptr<GameObject> obj)
{
    // 影描画用リストに追加
    objects_shadow_ready.push_back(obj);
}

void SharedData::InitializeAll()
{
    // エフェクト/弾などのマネージャ初期化 → ゲームオブジェクト初期化の順
    EffectCreator::GetEffectCreator().Initialize();
    for (auto object : objects_game)
    {
        object->Initialize();
    }
    BulletCreator::GetBulletCreator().Initialize();
}

void SharedData::UpdateTitle()
{
    // Titleシーン用更新（GameObject 側で Title 用処理を持つ前提）
    for (auto object : objects_game)
    {
        object->UpdateTitle();
    }
    if (ui) ui->UpdateTitle();
}

void SharedData::UpdateTutorial()
{
    // Tutorialシーン用更新
    for (auto object : objects_game)
    {
        object->UpdateTutorial();
    }
    if (ui) ui->UpdateTutorial();
}

void SharedData::UpdateGame()
{
    // 通常ゲーム中の更新
    for (auto object : objects_game)
    {
        object->Update();
    }

    // UI とエフェクトは GameObject とは別に更新
    if (ui) ui->Update();
    EffectCreator::GetEffectCreator().Update();
}

void SharedData::UpdateGameClear()
{
    // GameClearシーン用更新
    for (auto object : objects_game)
    {
        object->UpdateGameClear();
    }
    if (ui) ui->UpdateGameClear();
}

void SharedData::UpdateGameOver()
{
    // GameOverシーン用更新
    for (auto object : objects_game)
    {
        object->UpdateGameOver();
    }
    if (ui) ui->UpdateGameOver();
}

void SharedData::DrawShadowReady()
{
    // 影用に登録されたオブジェクトのみ描画
    for (auto object : objects_shadow_ready)
    {
        object->Draw();
    }
}

void SharedData::DrawTitle()
{
    // Titleシーンの描画
    for (auto object : objects_game)
    {
        object->Draw();
    }
    if (ui) ui->DrawTitle();

    // エフェクトはマネージャ経由でまとめて描画
    EffectCreator::GetEffectCreator().Draw();
}

void SharedData::DrawTutorial()
{
    // Tutorialシーンの描画
    for (auto object : objects_game)
    {
        object->Draw();
    }
    if (ui) ui->DrawTutorial();
    EffectCreator::GetEffectCreator().Draw();
}

void SharedData::DrawAll()
{
    // 通常ゲーム中の描画
    for (auto object : objects_game)
    {
        object->Draw();
    }
    if (ui) ui->Draw();
    EffectCreator::GetEffectCreator().Draw();
}

void SharedData::DrawGameClear()
{
    // GameClearシーンの描画
    for (auto object : objects_game)
    {
        object->Draw();
    }
    if (ui) ui->DrawGameClear();
    EffectCreator::GetEffectCreator().Draw();
}

void SharedData::DrawGameOver()
{
    // GameOverシーンの描画
    for (auto object : objects_game)
    {
        object->DrawGameOver();
    }

    // エフェクト描画 → UI描画
    EffectCreator::GetEffectCreator().Draw();
    if (ui) ui->DrawGameOver();
}

std::shared_ptr<GameObject> SharedData::FindObject(std::string_view obj_name)
{
    // 名前タグでGameObjectを検索
    for (auto object : objects_game)
    {
        if (object->GetNameTag() == obj_name)
        {
            return object;
        }
    }
    return nullptr;
}