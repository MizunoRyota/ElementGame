#pragma once

#include "PlayerStateBase.hpp"

class PlayerStateBase;
class BulletFire;

class PlayerAttack : public PlayerStateBase
{
public:
	PlayerAttack();
	~PlayerAttack();

	void Enter()override ;

	void Update()override ;

	void Exit()override ;

    PlayerStateKind GetNextState()override;

private:

	static constexpr float BULLETFIRE_DISTANCE = 2.0f; // 発射位置: 視線カメラからのオフセット  
	static constexpr float BULLET_SPEED = 0.6f;        // 弾速  

	std::shared_ptr<BulletFire>   player_bullet;   // 弾生成ハンドル  


};
