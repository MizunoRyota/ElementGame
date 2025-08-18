#pragma once
#include "EnemyAttackBase.hpp"

class EnemyWindAttack : public EnemyAttackBase
{
public:
	EnemyWindAttack(int modelhandle);
	~EnemyWindAttack()override;
	void Initialize()override;
	VECTOR Update(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle)override;
	bool IsAttackRange();		//攻撃範囲内かどうかの判定
	void MoveToPlayer();		//プレイヤーに向かって移動
	void Attack()override;
	void FireBullet();
	void PlayEffect()override;
	void UpdateBullet()override;
	void UpdateTargetBullet();
	void CheckOutBullet()override;
	bool GetIsAction()override;
	void DebugDraw() override;

private:
	static constexpr float BulletMoveSpeed = 0.2f;	//アニメーションを進める速度
	static constexpr float AttackRange = 14.0f;	//アニメーションを進める速度

	VECTOR position;
	VECTOR moveVec;
	VECTOR keep_distance;	//プレイヤーとの距離を保持するための変数
	float check_distance;	//プレイヤーとの距離を保持するための変数
	bool is_attack;
	VECTOR bullet_position[BulletNum];
	VECTOR bullet_startposition[BulletNum];
	VECTOR prevbullet_angle[BulletNum];
	bool isshot[BulletNum];
	bool shot_isout[BulletNum];
	int windeffect_handle[BulletNum];	 //リファクタリングで消す簡易的
	VECTOR attack_angle;
	VECTOR moveVecs[BulletNum];


	static constexpr  int BurstInterval = 45; // 10フレーム間隔で連射
	static constexpr float HomingDistance = 5.0f; // 追尾する最大距離
	bool isBurstShooting ;
	int burstShotCount ;
	int burstTimer ;
	bool bullet_homing[BulletNum]; // 弾ごとの追尾フラグ

};
