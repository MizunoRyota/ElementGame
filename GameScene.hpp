#pragma once
#include "Scene.hpp"

class SharedData;
class Player;
class Enemy;
class Shadow;
class BulletCreator;

/// @brief ステージシーン
class GameScene : public Scene
{
public:

    /// @brief SceneManager への参照を受け取ります。
    /// @param manager SceneManager への参照
    GameScene(SceneManager& manager, SharedData& sharedData);

    /// @brief ステージを初期化します。
    void Initialize() override;

    /// @brief ステージを更新します。
    void Update() override;

    /// @brief ステージを描画します。
    void Draw()  override;

private:

	std::shared_ptr<Shadow> shadow = nullptr; // 影オブジェクト

    std::shared_ptr<Player> player_reference = nullptr;

    std::shared_ptr<Enemy> enemy_reference = nullptr;

};
