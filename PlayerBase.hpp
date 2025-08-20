#pragma once
#include <memory>
#include <vector>
#include"PlayerMove.hpp"
#include "PlayerAttackManager.hpp"
class Stage;
class BulletManager;
class PlayerBase
{
public:

	PlayerBase();
	virtual ~PlayerBase();
	virtual void Initialize();		// 初期化処理.
	virtual void Update(const Input& input, const Camera& camera);			// 更新.
	void FireBullet(const Input& input, const Camera& camera);
	virtual void Draw() const;				// 描画.

	// モデルハンドルの取得.
	int GetModelHandle() const { return model_handle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetHandPosition() const { return hand_position; }

	void Setposition(const VECTOR set) { position = set; }

	void SetBulletManager(std::shared_ptr<BulletManager> bullet) { bullet_manager = bullet; }

private:
	static constexpr float Scale = 0.01f;	//モデルの大きさの倍数
	static constexpr float	ReturnRange = 19.0f;		// 移動速度
	int model_handle;	//モデルハンドル
	int hand_name;
	VECTOR hand_position;

	int current_state;	//現在のプレイヤーの状態
	VECTOR position;	// プレイヤーの座標
	std::shared_ptr<PlayerMove> player_move;
	std::shared_ptr<PlayerAttackManager> attack_manager;
	std::shared_ptr<BulletManager> bullet_manager;
	// 移動処理
	void Move(const VECTOR& MoveVector);
	void LimitRange();
};
