#pragma once
#include "Scene.hpp"

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
};
