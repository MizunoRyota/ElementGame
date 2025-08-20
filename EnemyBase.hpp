#pragma once
#include <memory>
#include <vector>
#include <random>  
#include <unordered_map>
#include "EnemyState.hpp"
#include "AnimaterBase.hpp"
#include "EnemyAttackManager.hpp"
#include "Bullet.hpp"

class Stage;

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();

	enum class AnimKind : int
	{
		Chase = 0,
		OnDamage = 1,
		Walkback = 2,
		Die = 3,
		GroundAttack = 4,
		RunLeft = 5,
		Change = 6,
		RunRight = 7,
		WindAttack = 8,
		WaterAttack = 9,
		FireAttack = 10,
		JumpAttack = 11,
		Idle = 12,
	};

	void Initialize();	//初期化
	virtual void Update(const VECTOR& playerpos, Stage& stage);	//更新
	void UpdateAngle(const VECTOR& player);						//向きの更新
	void Move(const VECTOR& MoveVector, Stage& stage);			//ポジションセット
	void UpdateStateAction(const VECTOR& playerpos);
	void Draw();

	//モデルのgetter
	int GetModelHandle() const { return enemy_modelhandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	void SetPos(const VECTOR set) { position = set; }

private:

	static constexpr float Scale = 0.025f;					//モデルの大きさの倍数

	int enemy_modelhandle;		//モデルハンドル
	int attackType ;
	float angle;			//方向
	VECTOR position;		//ポジション
	VECTOR angleVector;		//方向
	bool action_iswater;
	bool action_iswind;
	bool action_isfire;

	State state;
	
	//インスタンス生成
	std::shared_ptr<AnimaterBase> enemy_animater;
	std::shared_ptr<EnemyAttackManager> enemyattack_manager;
	std::shared_ptr<Bullet> bullets[100];
};