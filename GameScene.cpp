#include "stdafx.hpp"
#include "GameScene.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Shadow.hpp"
#include "BulletCreator.hpp"
#include "SharedData.hpp"
#include "CollisionSystem.hpp"
#include "EffectCreator.hpp"

GameScene::GameScene(SceneManager& manager, SharedData& sharedData)
    : Scene{ manager ,sharedData} {}

void GameScene::Initialize()
{
    // マウスカーソル非表示
    SetMouseDispFlag(FALSE);
    GetSharedData().InitializeAll();
    player_refrence = std::dynamic_pointer_cast<Player>(GetSharedData().FindObject("Player"));
    enemy_refrence = std::dynamic_pointer_cast<Enemy>(GetSharedData().FindObject("Enemy"));
    shadow = std::dynamic_pointer_cast<Shadow>(GetSharedData().FindObject("Shadow"));

    // エフェクト初期化
    EffectCreator::GetEffectCreator().Initialize();
}

void GameScene::Update()
{

    BulletCreator::GetBulletCreator().Update();
    GetSharedData().UpdateGame();

    // Effekseerにより再生中のエフェクトを更新する。
    // ★ 追加: すべての更新後に衝突判定を一括で解決
    CollisionSystem::Resolve(GetSharedData());

    // 置き換え: 直接UpdateEffekseer3D()ではなく、マネージャ更新
    EffectCreator::GetEffectCreator().Update();

    if (player_refrence->GetHp() <= 0 )
    {
        ChangeScene("GameOverScene");
    }
    else if (enemy_refrence->GetHp() <= 0)
    {
        ChangeScene("GameClearScene");
    }
}

void GameScene::Draw() 
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

    BulletCreator::GetBulletCreator().Draw();
    GetSharedData().DrawAll();

    // ここで一旦シャドウマップ適用を解除(エフェクトが暗くなる/欠けるのを防ぐ)
    SetUseShadowMap(0, -1);

    ScreenFlip();

}
