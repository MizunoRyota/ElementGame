#pragma once

#include "PlayerAttackBase.hpp"

class PlayerWaterAttack : public PlayerAttackBase
{
public:
	PlayerWaterAttack(int modelhandle);
	~PlayerWaterAttack()override;
	void Initialize()override;
	void Update(const Input& input, const Camera& camera)override;	// 更新.
	void PlayEffect()override;
	void Attack(const Input& input, const Camera& camera)override;
	void UpdateBullet(const Input& input, const Camera& camera)override;
	void CheckOutBullet()override;
	void CoolDown()override;
private:
	VECTOR bullet_position[BulletNum];
	VECTOR bullet_startposition[BulletNum];
	VECTOR prevbullet_angle[BulletNum];
	bool isshot[BulletNum];
	bool shot_isout[BulletNum];
	int watereffect_handle[BulletNum];	 //リファクタリングで消す簡易的

};
