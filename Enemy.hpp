#pragma once
#include "CharacterBase.hpp"
#include "EnemyState.hpp"
#include "EffectCreator.hpp" // 追加: エフェクト型参照

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
	};
	
	void Initialize()override; // 初期化
	
	void InitializeGame() { enemy_state = STATE_CHARGE; } // 初期化(ポジション指定)

	void Update()override; // 更新

	void UpdateGameClear() override; // ゲームクリア時更新
	void UpdateGameOver() override ;  // ゲームオーバー時更新
	void UpdateTitle() override ;     // タイトル時更新

	void UpdateStateAction()override; // ステートごとの更新

	void UpdateHandEffect();

	void UpdateAngle();

	void SetPosition(); // ポジションをセット

	void ChoseAttackType();

	void Draw()override;

	const VECTOR& GetHitPosition() const { return VAdd(obj_position,VGet(0, ENEMY_HITEFFECT_HEIGHT,0)); }

	const int& GetDamageStrength() const { return DAMAGE_STRENGTH; }

	void SetPos(const VECTOR set) { obj_position = set; }

	void SetPlayer(const std::shared_ptr<Player>& setplayer) { player_reference = setplayer; }

	float GetCapsuleRadius() const { return COLLISION_CAPSULE_RADIUS; }
	float GetCapsuleHeight() const { return COLLISION_CAPSULE_HEIGHT; }
	int GetEnemyState() const { return enemy_state; }

private:
	// ハンドエフェクト制御
	void StartHandEffectForAttack();
	void StopHandEffect();
	EffectCreator::EffectType MapEffectTypeForAttack(int attackState) const; // 宣言位置修正

	// ===== 衝突判定/カプセルパラメータ =====
	static constexpr float COLLISION_CAPSULE_RADIUS = 0.45f;   // カプセル半径(モデル合わせ & 衝突判定用)
	static constexpr float COLLISION_CAPSULE_HEIGHT = 2.75f;   // カプセル高さ(プレイヤー等との整合)

	// ===== 弾関連パラメータ =====
	static constexpr float FIREBULLET_SPEED = 0.40f;           // 火弾 速度
	static constexpr float FIREATTACK_TIMING = 30;             // 火弾 発射アニメフレーム
	static constexpr float WATERBULLET_SPEED = 0.20f;          // 水拡散弾 速度
	static constexpr float WATERATTACK_TIMING = 20;            // 水弾 発射アニメフレーム
	static constexpr float WINDBULLET_SPEED = 0.50f;           // 風(ホーミング)弾 速度
	static constexpr float WINDATTACK_TIMING = 40;             // 風弾 追尾開始(発射)アニメフレーム
	static constexpr float SPECIALBULLET_SPEED = 0.5f;         // 特殊攻撃(落下弾) 速度
	static constexpr float SPECIALEATTACK_TIMING = 35;         // 特殊攻撃 発射アニメフレーム
	static constexpr float BULLET_HIGHT = -0.5f;               // 発射位置オフセット(Y方向・モデル調整)
	
	// ===== ダメージ・HP・スケール =====
	static constexpr float TAKEDAMAGE_COOLDOWN = 10.0f;        // 被弾無敵時間(フレーム)
	static constexpr int DAMAGE_STRENGTH = 10;                 // 与ダメージ基礎値
	static constexpr float ENEMY_HITEFFECT_HEIGHT = 2.25f;       // 被弾エフェクトの高さオフセット
	static constexpr float ENEMY_SCALE = 0.02f;               // モデル拡大率
	static constexpr int ENEMY_MAXHP = 100;                    // 最大HP

	// ===== フェーズ用HP閾値 =====
	static constexpr int ENEMY_FHASE_ONE = 150;   // Phase1 開始HP
	static constexpr int ENEMY_FHASE_TWO = 100;   // Phase2 以降判定HP
	static constexpr int ENEMY_FHASE_THREE = 75;  // Phase3 以降判定HP
	static constexpr int ENEMY_FHASE_FOUR = 50;   // Phase4 以降判定HP
	static constexpr int ENEMY_FHASE_FIVE = 35;   // Phase5 (終盤) 判定HP

	// ===== 状態変数 =====
	int enemy_handname;                // モデル内の手(発射骨)フレーム名検索結果ID
	int enemy_attacktype;              // 次に実行する攻撃ステート種別 (EnemyState の値を格納)
	int enemy_dodgechose;              // 回避方向選択 (0:左 / 1:右)
	bool enemy_ischase;                // 追跡レンジ内かどうか
	bool enemy_isaction;               // 現在のアニメーションが終了したかどうか (trueで次遷移可)
	bool enemy_isdie;               // 死んだかどうか (trueで次遷移可)

	EnemyState enemy_state;            // 現在の行動ステート
	std::vector<int> attack_kind;      // ランダム選択用 攻撃ステート一覧 (STATE_FIRE/WATER/WINDATTACK)
	bool enemy_groundattack_charge_played = false; // SpecialChargeチャージエフェクト再生済みフラグ

	// ハンドエフェクト用再生ハンドル
	int enemy_hand_effect_handle = -1; 
	int enemy_hand_effect_attack_state = -1;      // どの攻撃種で作成したか

	// ===== コンポーネント(参照/所有) =====
	std::shared_ptr<AnimaterBase> enemy_animater;      // アニメーション制御
	std::shared_ptr<Dodge>       enemy_dodge;         // 回避挙動制御
	std::shared_ptr<Chase>       enemy_chase;         // 追跡判定/ロジック
	std::shared_ptr<BulletFire>  enemy_bullet;        // 弾生成/発射制御
	std::shared_ptr<SpecialAttack> enemy_specialattack; // 特殊攻撃状態管理(チャージなど)
	std::shared_ptr<EnemyMove>   enemy_move;          // 位置移動ロジック(原点復帰/追跡/浮上 等)

	std::shared_ptr<Player>      player_reference;     // プレイヤー参照 (位置/方向取得用)
};