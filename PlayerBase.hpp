#pragma once
#include <memory>
#include <vector>
#include"PlayerMove.hpp"
#include "PlayerAttackManager.hpp"
#include "PlayerState.hpp"
class Sound;
class Stage;
class BulletManager;
class AnimaterBase;
class PlayerBase
{
public:
	enum class AnimKind : int
	{

		Idle = 0,
		Attack = 0,

	};
	PlayerBase();
	virtual ~PlayerBase();
	virtual void Initialize();		// 初期化処理.
	virtual void Update(const Input& input, const Camera& camera);			// 更新.
	void TakeDamage(int damage);
	void FireBullet(const Input& input, const Camera& camera);
	void UpdateStateAction(const Input& input);

	virtual void Draw() const;				// 描画.

	// モデルハンドルの取得.
	int GetModelHandle() const { return model_handle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetHandPosition() const { return hand_position; }
	const int& GetHp() const { return hp; }

	void Setposition(const VECTOR set) { position = set; }
	void SetBulletManager(std::shared_ptr<BulletManager> bullet) { bullet_manager = bullet; }
	const int& GetDamageStrength() const { return damege_strength; }

private:
	static constexpr float Scale = 0.01f;	//モデルの大きさの倍数
	static constexpr float	ReturnRange = 19.0f;		// 移動速度
	static constexpr 	float firebullet_speed = 0.25f;
	static constexpr 	float waterbullet_speed = 0.25f;
	static constexpr 	float windbullet_speed = 0.25f;
	static constexpr 	int damege_strength = 1;
	static constexpr 	float takedamage_cooldown = 60.0f; // クールタイム秒数
	int model_handle;	//モデルハンドル
	int hand_name;
	float takedamage_cooldowntimer;

	int hp;		// プレイヤーのHP

	VECTOR hand_position;
	int current_state;	//現在のプレイヤーの状態
	VECTOR position;	// プレイヤーの座標
	std::shared_ptr<PlayerMove> player_move;
	std::shared_ptr<PlayerAttackManager> attack_manager;
	std::shared_ptr<BulletManager> bullet_manager;
	std::shared_ptr<AnimaterBase> player_animater;
	std::shared_ptr<Sound> sound_manager;	//サウンドマネージャー

	PlayerState player_state;

	// 移動処理
	void Move(const VECTOR& MoveVector);
	void LimitRange();
};
