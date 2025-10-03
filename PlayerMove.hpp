#pragma once
#include <memory>
class Camera;
class Input;

class PlayerMove
{
public:
	PlayerMove();
	~PlayerMove();

	void Update( std::shared_ptr<Input>& input,  std::shared_ptr<Camera>& camera);
	void UpdateMoveParameterWithPad( std::shared_ptr<Input>& input,  std::shared_ptr<Camera>& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	
	void MoveAngle(const VECTOR& targetPositon);
	void Move(const VECTOR& MoveVector);

	void DecreaseDashEnergy();

	// getter/setter.
	const VECTOR& GetMoveScale() const { return moveVec; }
	const float& GetMoceAngle() const { return move_angle; }
	const bool& GetIsmove() const { return move_ismove; }
	const bool& GetIsDash() const { return move_isdash; }
	int GetDashEnergy() const { return dash_energy; }
	int GetDashEnergyMax() const { return DASH_MAXENERGY; }
	int GetDashCooldown() const { return dash_cooldown; } // 残りクールタイム(0で使用可能)

private:
	static constexpr float	MOVE_SPEED = 0.075f;     // 移動速度
	static constexpr float	DASH_MULTIPLIER = 2.0f; // ダッシュ時の倍率
	static constexpr int	DASH_MAXENERGY = 50; // ダッシュの最大エネルギー(フレーム数)
	static constexpr int	DASH_COOLDOWN_FRAMES = 60; // エネルギー枯渇後のクールタイム(フレーム)

	static constexpr float	ANGLE_SPEED = 0.75f;    // 角度変化速度

	VECTOR move_targetdirection;                    // モデルが向くべき方向のベクトル
	VECTOR moveVec;                                 // このフレームの移動ベクトル
	
	bool move_ismove;                               // そのフレームで動いたかどうか
	bool move_isdash = false;                       // ダッシュ中か
	
	float move_angle;                               //プレイヤーが向く方向
	
	int dash_energy = DASH_MAXENERGY;               // 現在のダッシュエネルギー
	int dash_cooldown = 0;                          // 枯渇後クールタイム(0で未発動)
};

