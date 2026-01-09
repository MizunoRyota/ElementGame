#pragma once  
#include "CharacterBase.hpp"  
#include "PlayerStateKind.hpp"
class GameObject;  
class IState;
class CharaterBase;  
class AnimaterBase;  
class PlayerStateBase;
class PlayerMove;  
class Laser;
class BulletFire;  

// プレイヤーキャラクター  
class Player : public CharacterBase
{
public:
	Player();
	~Player()override;

	void Initialize() override;     // 初期化  

	void InitializeStates()override;

	void UpdateHandEffect()override;// 手元エフェクト更新  

	void Update() override;			// 毎フレーム更新  
	void Move();					// 位置・速度更新  
	void Draw() override;           // 描画  

	void UpdateStateAction() override; // ステートに応じた行動更新  
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};

	std::shared_ptr<PlayerMove> GetPlayerMove() const { return player_move; } // 移動コンポーネント取得
	PlayerStateKind GetPlayerStateKind()		const { return player_state_kind; } // 移動コンポーネント取得

	VECTOR GetLaserEndPosition();

private:
	// ===== 定数パラメータ =====  
	static constexpr float SCALE = 0.01f;               // モデルスケール  
	static constexpr int   PLAYER_MAXHP = 100;          // 最大HP  
	static constexpr float LASER_MAX_LENGTH = 30.0f;    // レーザーの距離

	// ===== コンポーネント =====  
	std::shared_ptr<AnimaterBase> player_animater;		// アニメーター  
	std::shared_ptr<PlayerMove>   player_move;			// 入力・移動ベクトル計算  

	//プレイヤーのステート
	std::shared_ptr<PlayerStateBase> player_current_state;
	std::unordered_map<PlayerStateKind, std::shared_ptr<PlayerStateBase>> states;
	// ===== 状態 =====  
	PlayerStateKind player_state_kind;

};