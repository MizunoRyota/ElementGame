#pragma once
#include "PlayerAttackBase.hpp"

class Input;
class Camera;

class PlayerFireAttack : public PlayerAttackBase
{
public:
	PlayerFireAttack(int modlehadle);
	~PlayerFireAttack()override;
	 void Initialize()override;
	 void Update(const Input& input, const Camera& camera)override;			// 更新.
	 void Attack(const Input& input, const Camera& camera)override;
	 void UpdateBullet(const Input& input, const Camera& camera)override;
	 void PlayEffect()override;
	 void CheckOutBullet()override;
	 void CoolDown()override;
private:
	VECTOR bullet_position;
	VECTOR bullet_startposition;
	VECTOR prevbullet_angle;
	bool isshot;
	bool shot_isout;
	int effect_handle; //リファクタリングで消す簡易的
};
