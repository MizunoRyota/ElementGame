#include "stdafx.hpp"
#include "GameScene.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Shadow.hpp"
#include "BulletCreator.hpp"
#include "SharedData.hpp"
#include "CollisionSystem.hpp"
#include "EffectCreator.hpp"
#include "src/Sounds/SoundManager.hpp"
#include "ObjectAccessor.hpp"
#include "CountdownOverlayUi.hpp"
#include "FightOverlayUi.hpp"

GameScene::GameScene(SceneManager& manager, SharedData& sharedData)
    : Scene{ manager ,sharedData} 
{
    countdown_one_graph_handle = LoadGraph("data/Texture/CountOne.png");
    countdown_two_graph_handle = LoadGraph("data/Texture/CountTwo.png");
    countdown_three_graph_handle = LoadGraph("data/Texture/CountThree.png");
    countdown_fight_graph_handle = LoadGraph("data/Texture/Fight.png");
}

void GameScene::Initialize()
{
    SetFontSize(60);
    // マウスカーソル非表示
    SetMouseDispFlag(FALSE);
    GetSharedData().InitializeAll();

    game_is_countdown = false;
    countdown_time = 0.0f;

    game_phase = Phase::Countdown;
    countdown_frame = COUNTDOWN_SECONDS * FPS;
    go_frame = FPS; // "GO"を1秒表示

    shadow = std::dynamic_pointer_cast<Shadow>(GetSharedData().FindObject("Shadow"));

    // エフェクト初期化
    EffectCreator::GetEffectCreator().Initialize();
	SoundManager::GetSoundManager().PlayGameBgm();
}

void GameScene::CountDown()
{
    if (game_phase != Phase::Countdown)
    {
        return;
    }

    if (countdown_frame > 0)
    {
        countdown_frame--;
        return;
    }

    if (go_frame > 0)
    {
        go_frame--;
        return;
    }

    game_phase = Phase::Playing;
    game_is_countdown = true;
}

void GameScene::Update()
{
    CountDown();

    if (game_phase == Phase::Countdown)
    {
        if (auto ui = GetSharedData().ui)
        {
            if (countdown_frame > 0)
            {
                const int sec = (countdown_frame + FPS - 1) / FPS;
                if (auto c = ui->FindElement<CountdownOverlayUi>()) c->SetSeconds(sec);
            }
            else
            {
                if (auto c = ui->FindElement<CountdownOverlayUi>()) c->SetSeconds(0);

                if (go_frame == FPS)
                {
                    if (auto f = ui->FindElement<FightOverlayUi>()) f->ShowForFrames(FPS);
                }
            }
        }

        GetSharedData().UpdateTutorial();
        EffectCreator::GetEffectCreator().Update();
        return;
    }

    BulletCreator::GetBulletCreator().Update();
    GetSharedData().UpdateGame();

    // Effekseerにより再生中のエフェクトを更新する。
    CollisionSystem::Resolve(GetSharedData());

    // 置き換え: 直接UpdateEffekseer3D()ではなく、マネージャ更新
    EffectCreator::GetEffectCreator().Update();

    if (ObjectAccessor::GetObjectAccessor().GetPlayerHp() <= 0 )
    {
        SoundManager::GetSoundManager().StopAllSound();
        BulletCreator::GetBulletCreator().StopBulletEffect();
        ObjectAccessor::GetObjectAccessor().StopEnemyHandEffect();
        ChangeScene("GameOverScene");
    }
    else if (ObjectAccessor::GetObjectAccessor().GetEnemyHp() <= 0)
    {
        SoundManager::GetSoundManager().StopAllSound();
        BulletCreator::GetBulletCreator().StopBulletEffect();
        ObjectAccessor::GetObjectAccessor().StopEnemyHandEffect();
        ChangeScene("GameClearScene");
    }
}

void GameScene::Draw() 
{

    ClearDrawScreen();

	//シャドウマップの準備
	ShadowMap_DrawSetup(shadow->GetHandle());

    GetSharedData().DrawShadowReady();
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
