#pragma once
#include <memory>
class Camera;
class Input;

class PlayerMove
{
public:
	PlayerMove();
	~PlayerMove();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="input"></param>
	/// <param name="camera"></param>
	void Update( std::shared_ptr<Input>& input,  std::shared_ptr<Camera>& camera);
	void UpdateMoveParameterWithPad( std::shared_ptr<Input>& input,  std::shared_ptr<Camera>& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	void MoveAngle(const VECTOR& targetPositon);
	void Move(const VECTOR& MoveVector);

	// getter/setter.
	const VECTOR& GetMoveScale() const { return moveVec; }
	const float& GetMoceAngle() const { return move_angle; }
	const bool& GetIsmove() const { return move_ismove; }

private:
	static constexpr float	MOVE_SPEED = 0.1f;		// 移動速度
	static constexpr float	ANGLE_SPEED = 0.75f;	// 角度変化速度

	VECTOR move_targetdirection;					// モデルが向くべき方向のベクトル
	VECTOR moveVec;									// このフレームの移動ベクトル
	
	bool move_ismove;								// そのフレームで動いたかどうか
	
	float move_angle;								//プレイヤーが向く方向
};

