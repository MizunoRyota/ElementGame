#pragma once

#include "GameObject.hpp" // 入力はゲーム内の汎用オブジェクトとして扱う

class GameObject;

// 入力
// ゲームパッドやキーボードの状態を取得して、ゲーム側に分かりやすい形に提供する
class Input : public GameObject
{
public:
	// アナログキーの方向ステート
	enum AnalogKeyState
	{
		AnalogRight = 1,    // 右
		AnalogLeft = 2,     // 左
		AnalogUp = 3,       // 上
		AnalogDown = 4,     // 下
	};

	//キーの種類
	enum KeyKinds
	{
		Move = 0,  //移動キーのどれか
		Left = 1,  //右
		Right = 2,  //左
		Up = 3,  //上
		Down = 4,  //下
	};

	//キーの押されている状態
	enum KeyPushState
	{
		NotPush = 0,  //押されていない
		JustRelease = 1,  //離された瞬間
		Push = 2,  //押されている
	};

	Input();
	~Input();

	void Initialize() override; // 初期化
	void Update() override;     // 入力更新
	void Draw() override;       // デバッグ描画等に使用

	// シーン別描画（入力は通常描画不要）
	void DrawTitle() override {};
	void DrawGameOver() override {};
	void DrawGameClear() override {};

	// シーン別更新（入力は共通で Update を呼ぶ想定のため通常何もしない）
	void UpdateGameClear() override { Update(); }
	void UpdateGameOver() override { Update(); }
	void UpdateTitle() override { Update(); }

	// 右スティックのアナログ方向が有効か
	bool IsInputAnalogKey(const AnalogKeyState analogKeyState);
	
	// 現在フレームに押されているボタンのビットフラグ
	int GetNowFrameInput() const { return input_nowframe; }
	// 現在フレームで新たに押されたボタンのビットフラグ
	int GetNowFrameNewInput() const { return input_newframe; }

	int GetInputType() const { return input_type; }

	XINPUT_STATE GetNowXInputState() { return input; }

private:
	static constexpr int ANALOGKEY_DEADZONE = 50; // スティック微動以下は無視する閾値

	XINPUT_STATE input;

	int input_nowframe;		// 現在フレームで押下中のボタン
	int input_newframe;		// 現在フレームで新規に押されたボタン
	int input_type;			// コントローラーが接続されているか判別
	int input_rightkey_x;	// 右アナログの水平入力値
	int input_rightkey_z;	// 右アナログの垂直入力値

};
