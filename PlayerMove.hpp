#pragma once
#include "ObjectAccessor.hpp"

class Camera;
class Input;

// プレイヤーの移動と向き管理
class PlayerMove
{
public:
	PlayerMove();
	~PlayerMove();

	void Update(); // 入力から移動更新
	void UpdateMoveParameterWithPad( VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec); // パッド入力から各ベクトルを算出
	
	void MoveAngle(const VECTOR& targetPositon); // 向き(角度)更新
	void Move(const VECTOR& MoveVector);         // 実移動適用

	void DecreaseDashEnergy();                   // ダッシュエネルギー減衰

	// getter/setter.
	const VECTOR& GetMoveScale()	const { return moveVec; }
	const float& GetMoveAngle()		const { return move_angle; }
	const bool& GetIsmove()			const { return move_is_move; }
	const bool& GetIsDash()			const { return move_is_dash; }
	float GetDashEnergy()			const { return dash_energy; }
	int GetDashEnergyMax()			const { return DASH_MAXENERGY; }
	int GetDashCooldown()			const { return dash_cooldown; } // 復帰クールタイム(0で使用可)

private:
	static constexpr float MOVE_SPEED = 0.075f;        // 基本移動速度
	static constexpr float DASH_MULTIPLIER = 2.0f;     // ダッシュ倍率
	static constexpr float DASH_DECREACE_NUM = 0.5f;   // フレーム毎のエネルギー減少
	static constexpr int   DASH_MAXENERGY = 30;        // 最大エネルギー
	static constexpr int   DASH_COOLDOWN_FRAMES = 60;  // クールタイム(フレーム)

	static constexpr float ANGLE_SPEED = 0.75f;        // 角度変化速度

	VECTOR move_targetdirection; // ターゲット方向のベクトル
	VECTOR moveVec;              // 今フレームの移動ベクトル
	
	bool move_is_move;            // 今フレーム移動を行ったか
	bool move_is_dash = false;    // ダッシュ中か
	
	float move_angle;            // プレイヤーの向き角
	
	float dash_energy = DASH_MAXENERGY; // 現在エネルギー
	int   dash_cooldown = 0;            // クールタイム(0で完了)
};

