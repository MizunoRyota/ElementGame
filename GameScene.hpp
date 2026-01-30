#pragma once
#include "Scene.hpp"

class SharedData;
class Player;
class Enemy;
class Shadow;
class BulletCreator;

///  ステージシーン
class GameScene : public Scene
{
public:

    ///  SceneManager への参照を受け取ります。
    /// @param manager SceneManager への参照
    GameScene(SceneManager& manager, SharedData& sharedData);

    ///  ステージを初期化します。
    void Initialize() override;

    ///  ステージを更新します。
    void Update() override;

    ///  ステージを描画します。
    void Draw()  override;

private:

	std::shared_ptr<Shadow> shadow = nullptr; // 影オブジェクト

};
