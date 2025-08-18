#pragma once
#include <memory>
#include <vector>
#include <random>  
#include"EnemyAnimationManager.hpp"
#include "EnemyAttackManager.hpp"

class Stage;

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();
	enum State
	{
		STATE_UNKNOWN,
		STATE_IDLE,
		STATE_CHARGE,
		STATE_TIRE,
		STATE_FIREATTACK,
		STATE_WATERATTACK,
		STATE_WINDATTACK,
		STATE_TURN,
		STATE_ONATTACK,
		STATE_DIE,
		STATE_JUMPATTACK,
		STATE_SLIDE
	};
	enum class AnimKind : int
	{
		Charge = 1,
		TireIdol = 2,
		Run = 3,
		Trun = 4,
		OnAttack = 5,
		Explosion = 6,
		Die = 7,
		JumpAttack = 8,
	};
	enum ColorState
	{
		STATE_GREEN,
		STATE_RED,
		STATE_BLUE,
	};

	void Initialize();	//初期化
	virtual void Update(const VECTOR& playerpos, Stage& stage);	//更新
	void UpdateAngle(const VECTOR& player);						//向きの更新
	void Move(const VECTOR& MoveVector, Stage& stage);			//ポジションセット
	void UpdateStateAction(const VECTOR& playerpos);
	void Draw();

	//モデルのgetter
	int GetModelHandle() const { return EnemyHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	void SetPos(const VECTOR set) { position = set; }

private:

	static constexpr float Scale = 0.025f;					//モデルの大きさの倍数

	int EnemyHandle;		//モデルハンドル
	int attackType ;
	float angle;			//方向
	VECTOR position;		//ポジション
	VECTOR angleVector;		//方向
	bool action_iswater;
	bool action_iswind;
	bool action_isfire;

	State state;
	//インスタンス生成
	std::shared_ptr<EnemyAnimationManager> enemyanimation_manager;
	std::shared_ptr<EnemyAttackManager> enemyattack_manager;
};