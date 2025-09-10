#include "stdafx.hpp"
#include "GameScene.hpp"
#include "Player.hpp"
#include "Shadow.hpp"
#include "BulletCreator.hpp"
#include "SharedData.hpp"

GameScene::GameScene(SceneManager& manager, SharedData& sharedData)
    : Scene{ manager ,sharedData} {}

void GameScene::Initialize()
{
    // マウスカーソル非表示
    SetMouseDispFlag(FALSE);
    GetSharedData().InitializeAll();
    player_refrence = std::dynamic_pointer_cast<Player>(GetSharedData().FindObject("Player"));
    shadow = std::dynamic_pointer_cast<Shadow>(GetSharedData().FindObject("Shadow"));
}

void GameScene::Update()
{

    BulletCreator::GetBulletCreator().Update();
    GetSharedData().UpdateAll();

    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();

    if (player_refrence->GetHp()<0)
    {
        ChangeScene("TitleScene");
    }
}

void GameScene::Draw() 
{

    ClearDrawScreen();

	//シャドウマップの準備
	ShadowMap_DrawSetup(shadow->GetHandle());

    GetSharedData().DrawAll();
    BulletCreator::GetBulletCreator().Draw();
	//シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

    // 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, shadow->GetHandle());

    GetSharedData().DrawAll();
    BulletCreator::GetBulletCreator().Draw();

    DrawEffekseer3D();

	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);

    ScreenFlip();

}
