#include "stdafx.hpp"
#include "GameClearScene.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Shadow.hpp"
#include "BulletCreator.hpp"
#include "SharedData.hpp"
#include "CollisionSystem.hpp"
#include "EffectCreator.hpp"

GameClearScene::GameClearScene(SceneManager& manager, SharedData& sharedData)
    : Scene{ manager ,sharedData } {
}

void GameClearScene::Initialize()
{
    // マウスカーソル非表示
    SetMouseDispFlag(TRUE);
    player_refrence = std::dynamic_pointer_cast<Player>(GetSharedData().FindObject("Player"));
    enemy_refrence = std::dynamic_pointer_cast<Enemy>(GetSharedData().FindObject("Enemy"));
    shadow = std::dynamic_pointer_cast<Shadow>(GetSharedData().FindObject("Shadow"));

    BulletCreator::GetBulletCreator().Initialize();
}

void GameClearScene::Update()
{

    bool check_isclick = ((GetMouseInput() & MOUSE_INPUT_LEFT));

    GetSharedData().UpdateGameClear();

    // 置き換え: 直接UpdateEffekseer3D()ではなく、マネージャ更新
    EffectCreator::GetEffectCreator().Update();

    if (check_isclick)
    {
        ChangeScene("TitleScene");
    }
}

void GameClearScene::Draw()
{

    ClearDrawScreen();

    //シャドウマップの準備
    ShadowMap_DrawSetup(shadow->GetHandle());

    GetSharedData().DrawShadowReady();
    BulletCreator::GetBulletCreator().Draw();
    //シャドウマップへの描画を終了
    ShadowMap_DrawEnd();

    // 描画に使用するシャドウマップを設定
    SetUseShadowMap(0, shadow->GetHandle());

    GetSharedData().DrawGameClear();
    BulletCreator::GetBulletCreator().Draw();

    // ここで一旦シャドウマップ適用を解除(エフェクトが暗くなる/欠けるのを防ぐ)
    SetUseShadowMap(0, -1);

    ScreenFlip();

}
