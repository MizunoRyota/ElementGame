#pragma once
#include "PlayerAttackBase.hpp"

class PlayerWindAttack : public PlayerAttackBase
{
public:
	PlayerWindAttack(int modelhandle);
	virtual ~PlayerWindAttack();
	void Initialize()override;
	void Update(const Input& input, const Camera& camera)override;			// 更新.
	void PlayEffect()override;
	void Attack(const Input& input, const Camera& camera)override;
	void UpdateBullet(const Input& input, const Camera& camera)override;
	void CheckOutBullet()override;
	void CoolDown()override;
private:
	VECTOR bullet_position[BulletNum];
	VECTOR bullet_startposition[BulletNum];
	VECTOR prevbullet_angle;
	bool isshot[BulletNum];
	bool shot_isout[BulletNum];
	int windeffect_handle[BulletNum] ;	 //リファクタリングで消す簡易的

};