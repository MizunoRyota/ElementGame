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

// ObjectAccessor:
// SharedData で生成した主要オブジェクトへの参照（`shared_ptr`）を保持し、
// ゲーム内のどこからでも「位置/状態/入力」など最低限の情報を取得できるようにする窓口。
//
// 使い方:
// - 基本的に `SharedData` 側の初期化で `Set*` を呼んで参照を登録する
// - 各クラスはここ経由で Player/Enemy/Camera/Input/Crystal の情報を取得する
//
// 注意:
// - `Get*` は登録済み（nullptrでない）ことを前提にしているため、
//   `Set*` 呼び出し前に利用するとクラッシュする可能性がある
class ObjectAccessor
{
public:

	// シングルトンインスタンス取得
	static ObjectAccessor& GetObjectAccessor()
	{
		static ObjectAccessor instance;
		return instance;
	}

	// --- 参照元をセット（SharedData 等の生成側で1回設定する想定） ---
	void SetPlayer(const std::shared_ptr<Player>& setplayer) { player_status = setplayer; }      // プレイヤー参照設定
	void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { enemy_status = setenemy; }           // エネミー参照設定
	void SetInput(const std::shared_ptr<Input>& setinput) { input_status = setinput; }          // インプット参照設定
	void SetCamera(const std::shared_ptr<Camera>& setcamera) { camera_status = setcamera; }     // カメラ参照設定
	void SetCrystal(const std::shared_ptr<Crystal>& setcrystal) { crystal_status = setcrystal; } // クリスタル参照設定

	// --- エネミー情報取得 ---
	VECTOR GetEnemyPosition()				const { return enemy_status->GetPosition(); }
	VECTOR GetEnemyGetHitPosition()			const { return enemy_status->GetHitPosition(); }
	VECTOR GetEnemyHandPosition()			const { return enemy_status->GetHandPosition(); }
	VECTOR GetEnemyDirection()				const { return enemy_status->GetEnemyDirection(); }
	EnemyStateKind GetEnemyStateKind()		const { return enemy_status->GetEnemyStateKind(); }
	int		GetEnemyHp()					const { return enemy_status->GetHp(); }
	int		GetEnemyMaxHp()					const { return enemy_status->GetEnemyMaxHp(); }
	float	GetEnemyAnimationFrame()		const { return enemy_status->GetAnimationFrame(); }
	bool	GetEnemyAnimaitonIsEnd()		const { return enemy_status->GetAnimationIsEnd(); }
	void	StopEnemyHandEffect()			const { return enemy_status->StopEnemyHandEffect(); }

	// --- プレイヤー情報取得 ---
	VECTOR GetPlayerPosition()				const { return player_status->GetPosition(); }
	VECTOR GetPlayerHandPosition()			const { return player_status->GetHandPosition(); }
	VECTOR GetLaserEndPosition()			const { return player_status->GetLaserEndPosition(); }
	VECTOR GetPlayerCapsuleTop()			const { return player_status->GetCapsuleTop(); }
	PlayerStateKind GetPlayerStateKind()	const { return player_status->GetPlayerStateKind(); }
	int	   GetPlayerHp()					const { return player_status->GetHp(); }
	void  ChangeIsReadyLaser(bool is_ready) const { return player_status->ChangeIsReadyLaser(is_ready); }
	bool  GetIsReadyLaser()				const { return player_status->GetIsReadyLaser(); }

	// --- クリスタル情報取得 ---
	bool GetCrystalIsBreak()				const { return crystal_status->GetCrystalIsBreak(); }
	bool GetCrystalIsInit()					const { return crystal_status->GetCrystalIsInit(); }
	int	 GetCrystalHp()						const { return crystal_status->GetHp(); }
	void ChangeCrystalIsBreak()				const { return crystal_status->ChangeCrystalIsBreak(); }

	// --- カメラ情報取得 ---
	VECTOR GetCameraDirection()				const { return camera_status->GetCameraDir(); }
	VECTOR GetCameraPosition()				const { return camera_status->GetPosition(); }
	VECTOR GetCameraTarget()				const { return camera_status->GetCameraTarget(); }
	void   StartShakeCamera()				const { return camera_status->StartShakeCamera(); }

	// --- 入力情報取得 ---
	// `Input` が保持する XInput 状態のラッパ
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

	// 入力のフレーム情報/入力種別
	int GetInputNowFrame()					const { return (input_status->GetNowFrameInput()); }
	int GetInputType()						const { return input_status->GetInputType(); }

private:

	ObjectAccessor() = default;
	~ObjectAccessor() = default;
	ObjectAccessor(const ObjectAccessor&) = delete;
	ObjectAccessor& operator=(const ObjectAccessor&) = delete;

	// 共有参照（SharedData が Set* して以降、各所から参照する）
	std::shared_ptr<Enemy> enemy_status;
	std::shared_ptr<Player> player_status;
	std::shared_ptr<Crystal> crystal_status;
	std::shared_ptr<Camera> camera_status;
	std::shared_ptr<Input> input_status;

};

