#pragma once
#include "EnemyAttackBase.hpp"

class EnemyFireAttack : public EnemyAttackBase
{
public:
	EnemyFireAttack(int modelhandle);
	~EnemyFireAttack()override;
	void Initialize()override;
	VECTOR Update(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)override;
	bool IsAttackRange();		//攻撃範囲内かどうかの判定
	void MoveToPlayer();		//プレイヤーに向かって移動
	void Attack()override;
	void UpdateBullet()override;
	void PlayEffect()override;
	void CheckOutBullet()override;
	bool GetIsAction()override;
	void DebugDraw() override;

private:
	static constexpr float MoveSpeed = 0.095f;	//アニメーションを進める速度
	static constexpr float AttackRange = 7.0f;	//アニメーションを進める速度
	VECTOR keep_distance;	//プレイヤーとの距離を保持するための変数
	float check_distance;	//プレイヤーとの距離を保持するための変数
	VECTOR position;
	VECTOR moveVec;
	VECTOR bullet_position;
	VECTOR attack_angle;
	VECTOR bullet_startposition;
	VECTOR prevbullet_angle;
	bool isshot;
	bool shot_isout;
	int effect_firehandle; //リファクタリングで消す簡易的
};
