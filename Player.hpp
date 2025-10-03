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

class Player : public CharacterBase
{
private:
	// プレイヤー用アニメーション種別（現在は使用シンプル）
	enum class AnimKind : int
	{
		Idle = 0,     // 待機
		Attack = 0,   // 攻撃(現状同値)
	};
public:
	Player();
	~Player()override;

	 void Initialize() override;   // 初期化
	 void Update()override;         // フレーム更新
	 void Move();                   // 位置更新
	 void Draw()override;           // 描画
	 void UpdateStateAction()override; // 入力に応じたステート更新＆攻撃処理

	 void UpdateGameClear() override {};
	 void UpdateGameOver() override {};
	 void UpdateTitle() override {};

	 void SetInput(const std::shared_ptr<Input>& setinput) { input_reference = setinput; }  // 入力参照設定
	 void SetCamera(const std::shared_ptr<Camera>& setcamera) { camera_reference = setcamera; } // カメラ参照設定
	 void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { enemy_reference = setenemy; } // 敵参照設定
	 void SetBulletManager(std::shared_ptr<BulletFire> bullet) { player_bullet = bullet; } // 弾生成管理設定

	 float GetCapsuleRadius() const { return COLLISION_CAPSULE_RADIUS; } // 衝突半径
	 float GetCapsuleHeight() const { return COLLISION_CAPSULE_HEIGHT; } // 衝突高さ
	 std::shared_ptr<PlayerMove> GetPlayerMove() const { return player_move; } // 移動制御取得

private:
	// ===== 定数パラメータ =====
	static constexpr float COLLISION_CAPSULE_RADIUS = 0.06f; // カプセル判定半径
	static constexpr float COLLISION_CAPSULE_HEIGHT = 2.5f;  // カプセル判定高さ
	static constexpr float BULLETFIRE_DISTANCE = 2.0f;       // 発射位置: 手→カメラ前方オフセット
	static constexpr float SCALE = 0.01f;                   // モデルスケール
	static constexpr float BULLET_SPEED = 0.6f;             // 自弾速度
	static constexpr int PLAYER_MAXHP = 100;                 // 最大HP

	// ===== 所持コンポーネント =====
	std::shared_ptr<AnimaterBase> player_animater; // アニメーション制御
	std::shared_ptr<PlayerMove>   player_move;     // 入力→移動ベクトル計算
	std::shared_ptr<BulletFire>   player_bullet;   // 弾発射ハンドラ

	// ===== 外部参照 =====
	std::shared_ptr<Camera> camera_reference = nullptr; // カメラ(向き/位置)
	std::shared_ptr<Input> input_reference = nullptr;   // 入力状態
	std::shared_ptr<Enemy> enemy_reference = nullptr;   // 近傍敵(将来ターゲット用)

	// ===== 状態 =====
	PlayerState player_state; // 現在のプレイヤー行動ステート
};
