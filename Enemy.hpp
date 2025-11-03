#pragma once
#include "CharacterBase.hpp"
#include "EnemyState.hpp"
#include "EffectCreator.hpp" // エフェクト生成

class GameObject;
class CharaterBase;
class Chase;
class Dodge;
class AnimaterBase;
class Player;
class BulletFire;
class SpecialAttack;
class EnemyMove;
class Palsy;

// 敵キャラクター
class Enemy :public CharacterBase
{
public:
	Enemy();
	~Enemy()override;

	// アニメ種別（モーションの識別に使用）
	enum class AnimKind : int
	{
		Plalsy = 0,
		WalkBack = 1,
		Die = 2,
		SpecialCharge = 3,
		Float = 4,
		SpecialAttack = 5,
		RunLeft = 6,
		Charge = 7,
		RunRight = 8,
		FireAttack = 9,
		WaterAttack = 10,
		WindAttack = 11,
		JumpAttack = 12,
		Idle = 13,
		Chase = 14,
		OnDamage = 15,
	};
	
	void Initialize()override; // 初期化
	
	void InitializeGame() { enemy_state = STATE_CHARGE; } // 開始状態の設定

	void Update()override; // 毎フレーム更新

	void UpdateGameClear() override; // クリア演出更新
	void UpdateGameOver() override ;  // ゲームオーバー演出更新
	void UpdateTitle() override ;     // タイトル時更新

	void UpdateStateAction()override; // ステートに応じた行動更新

	void UpdateHandEffect();          // 手エフェクトの更新

	void UpdateAngle();               // 向き更新（ターゲット方向など）

	void SetPosition(); // 位置設定（スポーン・復帰など）

	void ChoseAttackType();           // 攻撃種別を選択

	void ChangeStatePalsy();          // 麻痺状態へ遷移

	void Draw()override;              // 描画

	const VECTOR& GetHitPosition() const { return VAdd(obj_position,VGet(0, ENEMY_HITEFFECT_HEIGHT,0)); } // 被弾エフェクト座標

	const int& GetDamageStrength() const { return DAMAGE_STRENGTH; } // 与ダメージ量

	void SetPos(const VECTOR set) { obj_position = set; }            // 直接座標設定

	void SetPlayer(const std::shared_ptr<Player>& setplayer) { player_reference = setplayer; } // プレイヤー参照設定

	int GetEnemyState() const { return enemy_state; }                // 現在の状態取得

private:
	// 手エフェクト制御
	void StartHandEffectForAttack();
	void StopHandEffect();
	EffectCreator::EffectType MapEffectTypeForAttack(int attackState) const; // 攻撃ステートに応じたエフェクト種別へ変換

	// ===== 各種パラメータ =====
	static constexpr float FIREBULLET_SPEED = 0.40f;           // 火弾 速度
	static constexpr float FIREATTACK_TIMING = 30;             // 火攻撃 発射フレーム
	static constexpr float WATERBULLET_SPEED = 0.20f;          // 水弾 速度
	static constexpr float WATERATTACK_TIMING = 20;            // 水攻撃 発射フレーム
	static constexpr float WINDBULLET_SPEED = 0.50f;           // 風(ホーミング)弾 速度
	static constexpr float WINDATTACK_TIMING = 40;             // 風攻撃 予備動作開始(仮)フレーム
	static constexpr float SPECIALBULLET_SPEED = 0.5f;         // 特殊弾(地割れ等) 速度
	static constexpr float SPECIALEATTACK_TIMING = 35;         // 特殊攻撃 発射フレーム
	static constexpr float BULLET_HIGHT = -0.5f;               // 発射位置オフセット(Yが負で手前になる環境向け)
	
	// ===== ダメージ・HP・スケール =====
	static constexpr int DAMAGE_STRENGTH = 10;                 // 与ダメージ基本値
	static constexpr float ENEMY_HITEFFECT_HEIGHT = 2.25f;     // 被弾エフェクトの高さ
	static constexpr float ENEMY_SCALE = 0.02f;                // モデル拡大率
	static constexpr int ENEMY_MAXHP = 80;                     // 最大HP

	// ===== フェーズ用HPしきい値 =====
	static constexpr int ENEMY_FHASE_ONE = 150;   // Phase1 開始HP
	static constexpr int ENEMY_FHASE_TWO = 100;   // Phase2 以降HP
	static constexpr int ENEMY_FHASE_THREE = 75;  // Phase3 以降HP
	static constexpr int ENEMY_FHASE_FOUR = 50;   // Phase4 以降HP
	static constexpr int ENEMY_FHASE_FIVE = 35;   // Phase5(終盤) 以降HP

	// ===== 状態変数 =====
	int enemy_handname;                // モデル内「手」フレームのID
	int enemy_attacktype;              // 実行予定の攻撃ステート
	int enemy_dodgechose;              // 回避方向選択 (0:左 / 1:右)
	bool enemy_ischase;                // 追跡中か
	bool enemy_isaction;               // アクション中か(入力受付停止用)
	bool enemy_isdie;                  // 死亡しているか
	bool enemy_ispalsy;                // 麻痺しているか

	EnemyState enemy_state;            // 現在の行動ステート

	std::vector<int> attack_kind;      // ランダム選択用 攻撃ステート一覧

	bool enemy_groundattack_charge_played = false; // 特殊溜めエフェクト再生済みフラグ

	// 手エフェクト用ハンドル
	int enemy_hand_effect_handle = -1; 
	int enemy_hand_effect_attack_state = -1;      // どの攻撃で生成したか

	// ===== コンポーネント(追従/弾/回避 等) =====
	std::shared_ptr<AnimaterBase> enemy_animater;      // アニメーター
	std::shared_ptr<Dodge>       enemy_dodge;         // 回避ロジック
	std::shared_ptr<Chase>       enemy_chase;         // 追跡・経路
	std::shared_ptr<BulletFire>  enemy_bullet;        // 弾生成
	std::shared_ptr<SpecialAttack> enemy_specialattack; // 特殊攻撃制御
	std::shared_ptr<EnemyMove>   enemy_move;          // 位置更新(ワープ/追従/徘徊)
	std::shared_ptr<Palsy>       enemy_palsy;         // 麻痺処理
	std::shared_ptr<Player>      player_reference;    // プレイヤー参照
};