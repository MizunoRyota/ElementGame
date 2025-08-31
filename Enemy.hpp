#pragma once
#include "CharacterBase.hpp"
#include "EnemyState.hpp"

class GameObject;
class CharaterBase;
class Chase;
class AnimaterBase;
class Player;

class Enemy :public CharacterBase
{
public:
	Enemy();
	~Enemy()override;

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
	
	void Initialize()override;	//初期化
	
	void InitializeGame() { enemy_state = STATE_CHARGE; }	//初期化(ポジション指定)

	void Update()override;	//更新

	void UpdateStateAction()override;

	void SetPosition();

	void UpdateAngle();

	void Draw()override;

	//モデルのgetter
	int GetModelHandle() const { return obj_modelhandle; }
	const int& GetHp() const { return obj_hp; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return obj_position; }

	const int& GetDamageStrength() const { return DAMAGE_STRENGTH; }

	void SetPos(const VECTOR set) { obj_position = set; }

	//void SetBulletManager(std::shared_ptr<BulletManager> bullet) { bullet_manager = bullet; }

	void SetPlayer(const std::shared_ptr<Player>& setplayer) { player_refrence = setplayer; }

private:

	static constexpr	float ENEMY_SCALE = 0.025f;					//モデルの大きさの倍数
	static constexpr	int BULLET_NUM = 100;					//モデルの大きさの倍数
	static constexpr 	float FIREBULLET_SPEED = 0.25f;
	static constexpr 	float WATERBULLET_SPEED = 0.25f;
	static constexpr 	float WINDBULLET_SPEED = 0.25f;
	static constexpr 	int DAMAGE_STRENGTH = 10;
	static constexpr 	float TAKEDAMAGE_COOLDOWN = 60.0f; // クールタイム秒数

	int enemy_handname;

	int enemy_attacktype;

	bool enemy_ischase;

	bool enemy_isaction;

	EnemyState enemy_state;
	//インスタンス生成
	std::shared_ptr<AnimaterBase> enemy_animater;

	std::shared_ptr<Chase> enemy_chase;

	std::shared_ptr<Player> player_refrence;

};