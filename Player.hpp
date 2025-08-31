#pragma once
#include "CharacterBase.hpp"
#include "PlayerState.hpp"
class GameObject;
class CharaterBase;
class AnimaterBase;
class PlayerMove;
class Effect;
class Input;
class Camera;

class Player : public CharacterBase
{
private:
	enum class AnimKind : int
	{
		Idle = 0,
		Attack = 0,
	};
public:
	Player();
	~Player()override;
	 void Initialize() override;
	 void Update()override;
	 void Move();
	 void Draw()override;
	 void UpdateStateAction()override;
	 void SetInput(const std::shared_ptr<Input>& setinput) { input = setinput; }
	 void SetCamera(const std::shared_ptr<Camera>& setcamera) { camera = setcamera; }

private:

	// Ã“I’è”.
	static constexpr float SCALE = 0.01f;		//‘å‚«‚³
	static constexpr int PLAYER_MAXHP = 60;		//‘å‚«‚³

	std::shared_ptr<AnimaterBase> player_animater;
	std::shared_ptr<PlayerMove> player_move;

	std::shared_ptr<Camera> camera = nullptr;
	std::shared_ptr<Input>	input = nullptr;

	PlayerState player_state;

};
