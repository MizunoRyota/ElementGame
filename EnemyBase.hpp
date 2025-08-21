#pragma once
#include <memory>
#include <vector>
#include <random>  
#include <unordered_map>
#include "EnemyState.hpp"
#include "AnimaterBase.hpp"
#include "EnemyAttackManager.hpp"


class Stage;
class Sound;
class BulletManager;
class Chase;
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
	void InitializeGame() { state = STATE_CHARGE; }	//初期化(ポジション指定)
	virtual void Update(const VECTOR& playerpos, Stage& stage);	//更新
	void TakeDamage(int damage);
	void FireBullet(const float bullet_speed);

	void UpdateAngle(const VECTOR& player);						//向きの更新
	void Move(const VECTOR& MoveVector, Stage& stage);			//ポジションセット
	void UpdateStateAction(const VECTOR& playerpos);
	void UpdateGameClear();		//ゲームオーバーの更新
	void UpdateGameTitle();		//ゲームオーバーの更新
	void UpdateGameOver();		//ゲームオーバーの更新
	void Draw();

	//モデルのgetter
	int GetModelHandle() const { return enemy_modelhandle; }
	const int& GetHp() const { return hp; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }

	const int& GetDamageStrength() const { return damege_strength; }

	void SetPos(const VECTOR set) { position = set; }

	void SetBulletManager(std::shared_ptr<BulletManager> bullet) { bullet_manager = bullet; }

private:

	static constexpr float Scale = 0.025f;					//モデルの大きさの倍数
	static constexpr int BulletNUm = 100;					//モデルの大きさの倍数
	static constexpr 	float firebullet_speed = 0.25f;
	static constexpr 	float waterbullet_speed = 0.25f;
	static constexpr 	float windbullet_speed = 0.25f;
	static constexpr 	int damege_strength = 10;
	static constexpr 	float takedamage_cooldown = 60.0f; // クールタイム秒数

	int enemy_modelhandle;		//モデルハンドル
	int attackType ;
	float angle;			//方向
	VECTOR position;		//ポジション
	VECTOR angleVector;		//方向
	VECTOR hand_position;
	VECTOR bullet_startpos;
	bool action_iswater;
	bool action_iswind;
	bool action_isfire;

	State state;
	int hp;

	int hand_name;
	bool action_ischase;
	bool action_ischarge;
	
	float takedamage_cooldowntimer;
	//インスタンス生成
	std::shared_ptr<AnimaterBase> enemy_animater;
	std::shared_ptr<EnemyAttackManager> enemyattack_manager;
	std::shared_ptr<BulletManager> bullet_manager;
	std::shared_ptr <Chase> enemy_chase;
	std::shared_ptr<Sound> sound_manager;	//サウンドマネージャー
};