#pragma once
#include "Scene.hpp"

class SharedData;
class Player;
class Enemy;
class Shadow;
class BulletCreator;

/// @brief チュートリアルシーン
class TutorialScene : public Scene
{
public:
    /// @brief  SceneManager への参照を受け取る
    /// @param manager SceneManager への参照
    /// @param sharedData 共有データへの参照
    TutorialScene(SceneManager& manager, SharedData& sharedData);

    /// @brief ステージを初期化する
    void Initialize() override;

    /// @brief ステージを更新する
    void Update() override;

    /// @brief ステージを描画する
    void Draw()  override;

private:
    std::shared_ptr<Shadow> shadow = nullptr; ///< 影オブジェクト
    std::shared_ptr<Player> player_reference = nullptr; ///< プレイヤー参照
    std::shared_ptr<Enemy> enemy_reference = nullptr; ///< 敵キャラクター参照
};
