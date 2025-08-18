#pragma once
#include "EnemyAttackBase.hpp"
class EnemyWaterAttack : public EnemyAttackBase
{
public:
	EnemyWaterAttack(int modelhandle);
	~EnemyWaterAttack()override;

	void Initialize()override;

	VECTOR Update(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle) override;	//メインの更新
	 void PlayEffect()override;

	bool IsAttackRange();		//攻撃範囲内かどうかの判定
	void MoveToPlayer();		//プレイヤーに向かって移動
	void Attack();				//攻撃を行う
	void UpdateBullet()override;	//弾の起動更新
	void DebugDraw() override;
	const VECTOR& GetMoveScale() const { return moveVec; }
	void CheckOutBullet()override;
	bool GetIsAction()override;

private:
	static constexpr float MoveSpeed = 0.095f;	//アニメーションを進める速度
	static constexpr float AttackRange = 10.0f;	//アニメーションを進める速度

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
	int watereffect_handle[BulletNum];	 //リファクタリングで消す簡易的
	VECTOR attack_angle;
};

