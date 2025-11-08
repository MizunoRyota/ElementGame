#pragma once
#include "CharacterBase.hpp"
#include "PlayerState.hpp"

class GameObject;
class CharaterBase;
class AnimaterBase;
class PlayerMove;
class Input;
class Camera;
class BulletFire;
class Enemy;
class Laser;

// プレイヤーキャラクター
class Player : public CharacterBase
{
private:
	// プレイヤー用アニメ種別（現在はシンプル）
	enum class AnimKind : int
	{
		Idle = 0,     // 待機
		Attack = 0,   // 攻撃（仮で同値）
	};
public:
	Player();
	~Player()override;

	void Initialize() override;    // 初期化
	void Update() override;        // 毎フレーム更新
	void Move();                   // 位置・速度更新
	void Draw() override;          // 描画

	void UpdateStateAction() override; // ステートに応じた行動更新
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};

	void UpdateHandEffect();       // 手元エフェクト更新

	void SetInput(const std::shared_ptr<Input>& setinput) { input_reference = setinput; }    // 入力参照設定
	void SetCamera(const std::shared_ptr<Camera>& setcamera) { camera_reference = setcamera; } // カメラ参照設定
	void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { enemy_reference = setenemy; }    // 敵参照設定
	void SetBulletManager(std::shared_ptr<BulletFire> bullet) { player_bullet = bullet; }   // 弾マネージャ設定

	void PrepareLaser();

	std::shared_ptr<PlayerMove> GetPlayerMove() const { return player_move; } // 移動コンポーネント取得

private:
	// ===== 定数パラメータ =====
	static constexpr float BULLETFIRE_DISTANCE = 2.0f; // 発射位置: 視線カメラからのオフセット
	static constexpr float SCALE = 0.01f;              // モデルスケール
	static constexpr float BULLET_SPEED = 0.6f;        // 弾速
	static constexpr int   PLAYER_MAXHP = 100;         // 最大HP

	// ===== コンポーネント =====
	std::shared_ptr<AnimaterBase> player_animater; // アニメーター
	std::shared_ptr<PlayerMove>   player_move;     // 入力・移動ベクトル計算
	std::shared_ptr<BulletFire>   player_bullet;   // 弾生成ハンドル
	std::shared_ptr<Laser>		  player_laser;	   //　レーザー
	// ===== 参照 =====
	std::shared_ptr<Camera> camera_reference = nullptr; // カメラ(向き/位置)
	std::shared_ptr<Input> input_reference = nullptr;   // 入力
	std::shared_ptr<Enemy> enemy_reference = nullptr;   // 敵(ロックオン等)

	// ===== 状態 =====
	PlayerState player_state; // プレイヤー行動ステート
};