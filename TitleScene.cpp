#include "stdafx.hpp"

#include "TitleScene.hpp"
#include "GameObject.hpp"
#include "CharacterBase.hpp"
#include "SharedData.hpp"

TitleScene::TitleScene(SceneManager& manager, SharedData& sharedData)
    : Scene{ manager ,sharedData } {}

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{

    ChangeScene("GameScene");
}

void TitleScene::Draw() 
{
}
