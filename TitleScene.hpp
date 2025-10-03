#pragma once
#include "Scene.hpp"

class SharedData;
class Player;
class Enemy;
class Shadow;
class BulletCreator;

/// @brief タイトルシーン
class TitleScene : public Scene
{
public:

    /// @brief SceneManager への参照を受け取ります。
    /// @param manager SceneManager への参照
    TitleScene(SceneManager& manager, SharedData& sharedData);

    /// @brief タイトルを初期化します。
    void Initialize() override;

    /// @brief タイトルを更新します。
    void Update() override;

    /// @brief タイトルを描画します。
    void Draw() override;

private:
    std::shared_ptr<Shadow> shadow = nullptr; // 影オブジェクト

    std::shared_ptr<Player> player_refrence = nullptr;

    std::shared_ptr<Enemy> enemy_refrence = nullptr;

};
