#pragma once

class Camera;
class Input;

class PlayerMove 
{
public:
	PlayerMove();
	~PlayerMove();
	void Update(const Input& input, const Camera& camera);
	void UpdateMoveParameterWithPad(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	void MoveAngle(const VECTOR& targetPositon);
	void Move(const VECTOR& MoveVector);

	// getter/setter.
	const VECTOR& GetMoveScale() const { return moveVec; }
	const float& GetMoceAngle() const { return angle; }
	const bool& GetIsmove() const { return isMove;  }

private:
	VECTOR dir;
	static constexpr float	MoveSpeed = 0.1f;	// 移動速度
	static constexpr float	AngleSpeed = 0.75f;	// 角度変化速度
	VECTOR	targetMoveDirection;				// モデルが向くべき方向のベクトル
	VECTOR	moveVec;							// このフレームの移動ベクトル
	bool isMove;								// そのフレームで動いたかどうか
	float angle;								//プレイヤーが向く方向
};