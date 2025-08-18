#pragma once

class Input;
class Camera;

class PlayerAttackBase
{
public:

	PlayerAttackBase(int model_handle);
	virtual ~PlayerAttackBase();
	virtual void Initialize() = 0;
	virtual void Update(const Input& input, const Camera& camera);			// 更新.
	virtual void PlayEffect();
	virtual void Attack(const Input& input, const Camera& camera) = 0;
	virtual void UpdateBullet(const Input& input, const Camera& camera);
	virtual void CheckOutBullet() = 0;
	virtual void CoolDown() = 0;
	void Draw();
protected:
	
	static constexpr float EffectHight = -10.0f;	//再生しているエフェクトの高さ
	static constexpr float EffectScale = 0.1f;	//再生しているエフェクトの高さ
	static constexpr float BulletRange = 30.0f;	//再生しているエフェクトの高さ
	static constexpr float PlayEffectSpeed = 0.025f;	//再生速度
	static constexpr float EndTime = 30.0f;				//
	static constexpr float moveSpeed = 0.750f;			//
	static constexpr float attack_distance = 0.25f;		//
	static constexpr int BulletNum = 3;					//
	static constexpr float CooldownTime = 20; // 20フレームのクールダウン（約0.33秒）
	float cooldown_timer = 0; // 残りクールダウン時間
	VECTOR position;
	VECTOR AngleVec;
	int atkhandle;

	int playingEffectHandle;// 再生中のエフェクト
	float time;				// 時間を初期化する(定期的にエフェクトを再生するため)
	bool effect_isplay;			// エフェクトが再生中かどうかを示すフラグ
	bool effect_isend;				// エフェクトが終了したかどうかを示すフラグ

	int model_handle;
	int flame_name;
	int effect_handle;
};