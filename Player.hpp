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
	enum class AnimKind : int
	{
		Idle = 0,
		Attack = 0,
	};
public:
	Player();
	~Player()override;

	 void Initialize() override;	//初期化
	 void Update()override;			//更新
	 void Move();					//移動
	 void Draw()override;			//描画
	 void UpdateStateAction()override;//ステートごとの行動
	 void SetInput(const std::shared_ptr<Input>& setinput) { input_reference = setinput; }
	 void SetCamera(const std::shared_ptr<Camera>& setcamera) { camera_reference = setcamera; }
	 void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { enemy_reference = setenemy; }
	 void SetBulletManager(std::shared_ptr<BulletFire> bullet) { player_bullet = bullet; }

	 float GetCapsuleRadius() const { return COLLISION_CAPSULE_RADIUS; }
	 float GetCapsuleHeight() const { return COLLISION_CAPSULE_HEIGHT; }
private:

	// 静的定数.

	static constexpr float COLLISION_CAPSULE_RADIUS = 0.04f;   // モデルに合わせて調整
	static constexpr float COLLISION_CAPSULE_HEIGHT = 2.5f;   // Collision の CAPCULE_HIGHT と整合

	static constexpr float SCALE = 0.01f;				//モデルの大きさ
	static constexpr float BULLET_SPEED = 0.25f;		//弾の速さ

	static constexpr int PLAYER_MAXHP = 60;		//HPの最大値
	
	//インスタンスを作成
	std::shared_ptr<AnimaterBase> player_animater;
	std::shared_ptr<PlayerMove> player_move;
	std::shared_ptr<BulletFire> player_bullet;

	//参照用のインスタンスを作成
	std::shared_ptr<Camera> camera_reference = nullptr;
	std::shared_ptr<Input>	input_reference = nullptr;
	std::shared_ptr<Enemy> enemy_reference = nullptr;
	//プレイヤーのステート
	PlayerState player_state;

};
