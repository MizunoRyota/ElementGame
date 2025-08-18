#pragma once

class EnemyAnimationBase
{
public:
	EnemyAnimationBase(int modelhandle);
	virtual~EnemyAnimationBase();
public:
	// 状態
	struct AnimationState
	{
		int		AnimationNum =0;				// 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
		float	TotalAnimationTime = 0;			// 再生しているアニメーションの再生時間
		float   AnimTime = 0;					// 現在のアニメーション再時間
		float	PlayAnimSpeed = 0;				// アニメーションを進める速さ
	};
	enum class AnimKind : int
	{
		Idle = 1,
		TireIdol = 2,
		Run = 3,
		Trun = 4,
		OnAttack = 5,
		Explosion = 6,
		Die = 7,
		JumpAttack = 8,
	};
	void Initialize(AnimationState state, int animnum);
	void ChangeMotion(AnimationState newstate);
	void UpdateAnimation(AnimationState prevstate, AnimationState newstate);
	void DetachAnimation(AnimationState newstate);
	void Update(AnimationState prevstate, AnimationState newstate);
	void SwitchAnimation(AnimationState newstate);

	const AnimationState& GetCurrentState() const { return currentState; }
	void SetCurrentState(const AnimationState set) { currentState = set; }
protected:
	// プレイヤー関係の定義
	static constexpr float	AnimBlendSpeed = 0.1f;		// アニメーションのブレンド率変化速度
	float		animBlendRate;				// 現在と過去のアニメーションのブレンド率
	int			modelHandle;				// 敵のモデルハンドル	
	int			bottom_handle;				//
	bool		effect_isplayAnim;					//
	AnimationState prevState;				// ひとつ前の状態
	AnimationState currentState;			// 現在の状態
	AnimationState newState;				// 次の状態

};