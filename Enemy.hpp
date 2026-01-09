#pragma once
#include "CharacterBase.hpp"
#include "EnemyStateKind.hpp"
#include "AnimaterBase.hpp"
#include "EffectCreator.hpp" // エフェクト生成

class GameObject;
class CharaterBase;
class EnemyStateBase;
class AnimaterBase;
class EnemyAnimater;
class Player;
class BulletFire;
class EnemyMove;
class SpecialAttack;

// 敵キャラクター
class Enemy :public CharacterBase
{
public:
	Enemy();
	~Enemy()override;
	
	void Initialize()override; // 初期化
	
	void InitializeStates()override;

	void InitializeGame() { enemy_state = EnemyStateKind::STATE_CHARGE; } // 開始状態の設定

	void Update()override; // 毎フレーム更新

	void UpdateGameClear() override;  // クリア演出更新
	void UpdateGameOver() override ;  // ゲームオーバー演出更新
	void UpdateTitle() override ;     // タイトル時更新

	void UpdateStateAction()override; // ステートに応じた行動更新

	void UpdateHandEffect()override;  // 手エフェクトの更新

	void UpdateAngle();               // 向き更新（ターゲット方向など）

	void SetPosition();				  // 位置設定（スポーン・復帰など）

	void Draw()override;              // 描画

	const VECTOR& GetHitPosition()				const { return VAdd(obj_position,VGet(0, ENEMY_HITEFFECT_HEIGHT,0)); } // 被弾エフェクト座標

	const VECTOR& GetEnemyDirection()			const { return obj_direction; } // 被弾エフェクト座標

	const EnemyStateKind& GetEnemyStateKind()	const { return enemy_state_kind; }

	const int& GetDamageStrength()				const { return DAMAGE_STRENGTH; } // 与ダメージ量

	const bool& GetAnimationIsEnd()				const { return enemy_animater->GetAmimIsEnd(); }

	const float& GetAnimationFrame()			const { return enemy_animater->GetAnimationFrame(); }

private:

	void StopHandEffect();
	
	// ===== ダメージ・HP・スケール =====
	static constexpr int DAMAGE_STRENGTH = 10;                 // 与ダメージ基本値
	static constexpr float ENEMY_HITEFFECT_HEIGHT = 2.5f;      // 被弾エフェクトの高さ
	static constexpr float ENEMY_SCALE = 0.02f;                // モデル拡大率
	static constexpr int ENEMY_MAXHP = 100;                    // 最大HP

	// ===== フェーズ用HPしきい値 =====
	//static constexpr int ENEMY_FHASE_ONE = 150;   // Phase1 開始HP
	static constexpr int ENEMY_FHASE_TWO = 100;     // Phase2 以降HP
	static constexpr int ENEMY_FHASE_THREE = 75;    // Phase3 以降HP

	// ===== 状態変数 =====
	int enemy_handname;						// モデル内「手」フレームのID
	bool enemy_is_die;						// 死亡しているか
	bool enemy_is_keep_state;				// ステートの状態を保持しているか
	EnemyStateKind enemy_state;				// 現在の行動ステート
	EnemyStateKind enemy_keep_state;		// 保持しているステート

	// 手エフェクト用ハンドル
	int enemy_hand_effect_handle = -1; 
	int enemy_hand_effect_attack_state = -1;		// どの攻撃で生成したか

	// ===== コンポーネント(追従/弾/回避 等) =====
	std::shared_ptr<AnimaterBase> enemy_animater;		// アニメーター
	std::shared_ptr<EnemyMove>   enemy_move;            // 位置更新(ワープ/追従/徘徊)

	////エネミーのステート
	std::shared_ptr<EnemyStateBase> enemy_current_state;
	std::unordered_map<EnemyStateKind, std::shared_ptr<EnemyStateBase>> states;
	// ===== 状態 =====  
	EnemyStateKind enemy_state_kind;
};