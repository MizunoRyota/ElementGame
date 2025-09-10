#pragma once
#include "CharacterBase.hpp"
#include "EnemyState.hpp"

class GameObject;
class CharaterBase;
class Chase;
class Dodge;
class AnimaterBase;
class Player;
class BulletFire;
class SpecialAttack;
class EnemyMove;

class Enemy :public CharacterBase
{
public:
	Enemy();
	~Enemy()override;

	enum class AnimKind : int
	{
		OnDamage = 0,
		Walkback = 1,
		Die = 2,
		GroundAttack = 3,
		Float = 4,
		SpecialAttack = 5,
		RunLeft = 6,
		Charge = 7,
		RunRight = 8,
		WindAttack = 9,
		WaterAttack = 10,
		FireAttack = 11,
		JumpAttack = 12,
		Idle = 13,
		Chase = 14,
	};
	
	void Initialize()override;	//初期化
	
	void InitializeGame() { enemy_state = STATE_CHARGE; }	//初期化(ポジション指定)

	void Update()override;	//更新

	void UpdateStateAction()override;	//ステートごとの更新

	void SetPosition();		//ポジションをセット

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

	static constexpr	float ENEMY_SCALE = 0.025f;			//モデルの大きさの倍数
	static constexpr 	float FIREBULLET_SPEED = 0.25f;
	static constexpr 	float WATERBULLET_SPEED = 0.25f;
	static constexpr 	float WINDBULLET_SPEED = 0.25f;
	static constexpr 	int DAMAGE_STRENGTH = 10;
	static constexpr 	float TAKEDAMAGE_COOLDOWN = 60.0f;  // クールタイム秒数
	static constexpr	float BULLET_HIGHT = -0.5f;			//モデルの大きさの倍数

	int enemy_handname;

	int enemy_attacktype;

	bool enemy_ischase;

	bool enemy_isaction;

	EnemyState enemy_state;

	//インスタンス生成
	std::shared_ptr<AnimaterBase> enemy_animater;

	std::shared_ptr<Dodge> enemy_dodge;

	std::shared_ptr<Chase> enemy_chase;

	std::shared_ptr<Player> player_refrence;

	std::shared_ptr<BulletFire> enemy_bullet;

	std::shared_ptr<SpecialAttack> enemy_specialattack;

	std::shared_ptr<EnemyMove> enemy_move;

};