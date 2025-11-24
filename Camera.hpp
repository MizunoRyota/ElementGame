#pragma once
#include "GameObject.hpp"

class Input;
class GameObject;
class Player;
class Enemy;

// カメラ（TPS想定）。プレイヤー位置や入力に応じて注視点と位置を更新する。
class Camera : public GameObject
{
public:
    Camera();            // コンストラクタ
    ~Camera();           // デストラクタ

    void Initialize() override;        // 初期化

    // シーン別更新
    void UpdateTitle() override;       // タイトル時のカメラ更新
    void Update() override;            // 通常更新（プレイ中）
    void UpdateGameClear() override;   // ゲームクリア時の演出更新（注視移動）
    void UpdateGameOver() override { UpdateGameClear(); } // ゲームオーバー時はクリアと同じ

    // シーン別描画（カメラは通常描画不要）
    void DrawTitle() override {}
    void Draw() override {}
    void DrawGameOver() override {}
    void DrawGameClear() override {}

    void StartShakeCamera();//camera_shakeをtrueにする
    void ShakeCamera();  //カメラ揺らし

    // 位置補間
    // camera_pos: 現在位置, target_pos: 目標位置, t: 0?1 の補間係数
    VECTOR Lerp(const VECTOR& camera_pos, const VECTOR& target_pos, float t);

    //void FixCameraPosition();          // カメラを固定位置へ戻す（必要に応じて使用）

    // 位置・向き取得
    const VECTOR& GetPosition()     const { return obj_position; }
    const VECTOR& GetCameraTarget() const { return camera_targetpos; }
    const VECTOR& GetCameraDir()    const { return camera_dirction; }

    // 参照対象設定
    void SetPlayer(const std::shared_ptr<Player>& setplayer) { player = setplayer; }
    void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { enemy = setenemy; }

private:
    // カメラ定数
    static constexpr float CAMERA_NEAR = 0.1f;                // ニア
    static constexpr float CAMERA_FAR = 600.0f;               // ファー
    static constexpr float CAMERA_TARGET_PLAYERHIGHT = 0.650f;// プレイヤーヘッドへのオフセット
    static constexpr float TOPLAYER_LENGTH = 1.30f;           // プレイヤーとの距離
    static constexpr float ANGLE_SPEED = 0.04f;               // 角速度
    static constexpr float CAMERA_PLAYERTARGET_HIGHT = 1.8f;  // プレイヤー注視点の高さ
    static constexpr float CAMERA_MAX_SHAKETIME = 5.0f;      // カメラを揺らす時間
    static constexpr float CAMERA_SHAKESPEED = 0.1f;      // カメラを揺らす時間

    static constexpr float CAMERA_FOV = 70.0f;                // 視野角

    // 制御用変数
    float  camera_angle_virtual;       // ピッチ角（上下）
    float  camera_angle_horizontal;    // ヨー角（左右）
    float  shakeOffset;                // シェイクのオフセット量

    float  camera_shaketime;           // シェイク時間
    bool   camera_shake;                    // シェイク中フラグ
    Input* rightInput;                 // 入力（右スティック等）

    VECTOR OriginalOffset;             // 位置オフセットの初期値
    VECTOR camera_angle;               // 角度ベクトル
    VECTOR obj_position;               // カメラ位置
    VECTOR camera_targetpos;           // 注視点
    VECTOR camera_dirction;            // 方向ベクトル（注視点-位置）

    std::shared_ptr<Player> player;    // 参照：プレイヤー
    std::shared_ptr<Enemy>  enemy;     // 参照：敵
};