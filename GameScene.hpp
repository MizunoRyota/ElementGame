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

    void CountDown();

    ///  ステージを更新します。
    void Update() override;

    ///  ステージを描画します。
    void Draw()  override;

    void  DrawCountdownOverlay(int seconds);

    void DrawFightOverlay();

private:

	std::shared_ptr<Shadow> shadow = nullptr; // 影オブジェクト

    enum class Phase
    {
        Countdown,
        Playing,
    };

    static constexpr int COUNTDOWN_SECONDS = 3;
    static constexpr int FPS = 60;

    Phase game_phase = Phase::Countdown;
    int countdown_frame = 0;
    int go_frame = 0;

    bool game_is_countdown;
    float countdown_time;

    int countdown_one_graph_handle;
    int countdown_two_graph_handle;
    int countdown_three_graph_handle;
    int countdown_fight_graph_handle;


};
