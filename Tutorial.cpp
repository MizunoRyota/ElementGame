#include "stdafx.hpp"
#include "Tutorial.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Shadow.hpp"
#include "BulletCreator.hpp"
#include "SharedData.hpp"
#include "EffectCreator.hpp"
#include "src/Sounds/SoundManager.hpp"
#include "ObjectAccessor.hpp"

TutorialScene::TutorialScene(SceneManager& manager, SharedData& sharedData)
    : Scene{ manager ,sharedData } {
}

void TutorialScene::Initialize()
{
    // マウスカーソル非表示
    SetMouseDispFlag(FALSE);
    GetSharedData().InitializeAll();
    player_reference = std::dynamic_pointer_cast<Player>(GetSharedData().FindObject("Player"));
    enemy_reference = std::dynamic_pointer_cast<Enemy>(GetSharedData().FindObject("Enemy"));
    shadow = std::dynamic_pointer_cast<Shadow>(GetSharedData().FindObject("Shadow"));

    // エフェクト初期化
    EffectCreator::GetEffectCreator().Initialize();
	SoundManager::GetSoundManager().PlayTutorialBgm();
}

void TutorialScene::Update()
{

    bool check_is_click = ((GetMouseInput() & MOUSE_INPUT_LEFT));

    GetSharedData().UpdateTutorial();

    // 置き換え: 直接UpdateEffekseer3D()ではなく、マネージャ更新
    EffectCreator::GetEffectCreator().Update();

    if (check_is_click || ObjectAccessor::GetObjectAccessor().GetIsInputBottunA())
    {
        SoundManager::GetSoundManager().PlayButtonSe();
        SoundManager::GetSoundManager().StopAllSound();
        ChangeScene("GameScene");
    }
}

void TutorialScene::Draw()
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

    GetSharedData().DrawTutorial();
    BulletCreator::GetBulletCreator().Draw();

    // ここで一旦シャドウマップ適用を解除(エフェクトが暗くなる/欠けるのを防ぐ)
    SetUseShadowMap(0, -1);

    ScreenFlip();

}
