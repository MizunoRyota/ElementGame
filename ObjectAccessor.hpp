#pragma once
#include "stdafx.hpp"
#include "Enemy.hpp" 
#include "Player.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Crystal.hpp"

class Crystal;
class Input;
class Player;
class Enemy;
class Camera;

class ObjectAccessor
{
public:

	static ObjectAccessor& GetObjectAccessor()
	{
		static ObjectAccessor instance; // シングルトン
		return instance;
	}

	//参照元をセット
	void SetPlayer(const std::shared_ptr<Player>& setplayer) { player_status = setplayer; }		 // プレイヤー参照設定
	void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { enemy_status = setenemy; }			 // エネミー参照設定
	void SetInput(const std::shared_ptr<Input>& setcamera) { input_status = setcamera; }		 // インプット参照設定
	void SetCamera(const std::shared_ptr<Camera>& setcamera) { camera_status = setcamera; }		 // カメラ参照設定
	void SetCrystal(const std::shared_ptr<Crystal>& setcrystal) { crystal_status = setcrystal; } // クリスタル参照設定

	//エネミーの参照渡し
	VECTOR GetEnemyPosition()				const { return enemy_status->GetPosition(); }
	VECTOR GetEnemyGetHitPosition()			const { return enemy_status->GetHitPosition(); }
	VECTOR GetEnemyHandPosition()			const { return enemy_status->GetHandPosition(); }
	VECTOR GetEnemyDirection()				const { return enemy_status->GetEnemyDirection(); }
	EnemyStateKind GetEnemyStateKind()		const { return enemy_status->GetEnemyStateKind(); }
	int		GetEnemyHp()					const { return enemy_status->GetHp(); }
	int		GetEnemyMaxHp()					const { return enemy_status->GetEnemyMaxHp(); }
	float	GetEnemyAnimationFrame()		const { return enemy_status->GetAnimationFrame(); }
	bool	GetEnemyAnimaitonIsEnd()		const { return enemy_status->GetAnimationIsEnd(); }
	void	StopEnemyHandEffect()			const { enemy_status->StopEnemyHandEffect(); }


	//プレイヤーの参照渡し
	VECTOR GetPlayerPosition()				const  { return player_status->GetPosition(); }
	VECTOR GetPlayerHandPosition()			const { return player_status->GetHandPosition(); }
	VECTOR GetLaserEndPosition()			const { return player_status->GetLaserEndPosition(); }
	VECTOR GetPlayerCapsuleTop()			const { return player_status->GetCapsuleTop(); }
	PlayerStateKind GetPlayerStateKind()	const { return player_status->GetPlayerStateKind(); }
	int	   GetPlayerHp()					const { return player_status->GetHp(); }

	//クリスタルの参照渡し
	bool GetCrystalIsBreak()				const { return crystal_status->GetCrystalIsBreak(); }
	bool GetCrystalIsInit()					const { return crystal_status->GetCrystalIsInit(); }

    void ChangeCrystalIsBreak()				const { return crystal_status->ChangeCrystalIsBreak(); }
	//カメラの参照渡し
	VECTOR GetCameraDirection()				const { return camera_status->GetCameraDir(); }
	VECTOR GetCameraPosition()				const { return camera_status->GetPosition(); }
	VECTOR GetCameraTarget()				const { return camera_status->GetCameraTarget(); }
	void   StartShakeCamera()				const { return camera_status->StartShakeCamera(); }

	//インプットの参照渡し
	bool GetIsInputRightTrigger()			const { return (input_status->GetNowXInputState().RightTrigger); }
	bool GetIsInputLeftTrigger()			const { return (input_status->GetNowXInputState().LeftTrigger); }
	bool GetIsInputLeftThumb()				const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_LEFT_THUMB]); }
	bool GetIsInputLeftShoulder()			const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_LEFT_SHOULDER]); }
	bool GetIsInputRightThumb()				const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_RIGHT_THUMB]); }
	bool GetIsInputRightShoulder()			const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]); }
	bool GetIsInputBottunY()				const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_Y]); }
	bool GetIsInputBottunA()				const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_A]); }
	bool GetIsInputBottunX()				const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_X]); }
	bool GetIsInputBottunB()				const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_B]); }

	bool GetIsInputUp()						const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_DPAD_UP]); }
	bool GetIsInputDown()					const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_DPAD_DOWN]); }
	bool GetIsInputRight()					const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_DPAD_RIGHT]); }
	bool GetIsInputLeft()					const { return (input_status->GetNowXInputState().Buttons[XINPUT_BUTTON_DPAD_LEFT]); }

	int GetInputNowFrame()					const { return (input_status->GetNowFrameInput()); }
	int GetInputType()						const { return input_status->GetInputType(); }

private:

	ObjectAccessor() = default;
	~ObjectAccessor() = default;
	ObjectAccessor(const ObjectAccessor&) = delete;
	ObjectAccessor& operator=(const ObjectAccessor&) = delete;

	std::shared_ptr<Enemy> enemy_status;
	std::shared_ptr<Player> player_status;
	std::shared_ptr<Crystal> crystal_status;
	std::shared_ptr<Camera> camera_status;
	std::shared_ptr<Input> input_status;

};

