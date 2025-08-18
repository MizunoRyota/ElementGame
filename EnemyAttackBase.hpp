#pragma once
#include <memory>
#include <vector>

class EnemyAttackBase
{
public:
	EnemyAttackBase(int modelhandle); // 追加
	virtual ~EnemyAttackBase(); 
	virtual void Initialize() = 0;
	virtual VECTOR Update(const VECTOR& playerpos, const VECTOR& enemypos, const VECTOR& angle) = 0;
	virtual void Attack()=0;
	virtual void PlayEffect();
	virtual void UpdateBullet();
	virtual void CheckOutBullet() = 0;
	virtual bool GetIsAction() = 0;
	virtual void DebugDraw();
	void Draw();
protected:
	static constexpr int BulletNum = 3;			//アニメーションを進める速度
	static constexpr float PlayEffectSpeed = 0.0250f;	//再生速度
	static constexpr float EndTime = 30.0f;		//再生速度
	static constexpr float MoveSpeed = 0.10f;	//再生速度
	static constexpr float BulletMoveSpeed = 0.2f;	//アニメーションを進める速度

	static constexpr float InitializePosition = -10.0f;
	static constexpr float EffectHight = -10.0f;	//再生しているエフェクトの高さ
	static constexpr float BulletRange = 20.0f;	//再生しているエフェクトの高さ

	bool isattack_jumpattack;
	int model_handle;
	int flame_name;
	int effect_handle;
	bool effect_isplay;
	bool effect_isend;
	bool bullet_isattack;
	int playingEffectHandle;// 再生中のエフェクト
	float effect_playtime;				// 時間を初期化する(定期的にエフェクトを再生するため)
	VECTOR enemy_position;
	VECTOR player_position;
	VECTOR angle_vector;
	VECTOR toTarget;
	VECTOR check_direction;
	static constexpr float EffectScale = 1.0f;	//再生しているエフェクトの高さ

	float time;				// 時間を初期化する(定期的にエフェクトを再生するため)

	bool action_isend;
};