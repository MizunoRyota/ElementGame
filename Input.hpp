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

	// キーの種類
	enum KeyKinds
	{
		Move = 0,   // 移動キーのどれか
		Left = 1,   // 左
		Right = 2,  // 右
		Up = 3,     // 上
		Down = 4,   // 下
		Space = 5,  // スペース
		LB = 6,     // 左肩のボタン
		LT = 7,     // 左肩のトリガー
		RB = 8,     // 右肩のボタン
		RT = 9,     // 右肩のトリガー
		X = 10,
		Y = 11,
		A = 12,
		B = 13,
		LeftStick = 14,  // 左スティック押し込み
		None = 15,       // 使用しないキーまたは未定義
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
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};

	// 右スティックのアナログ方向が有効か
	bool IsInputAnalogKey(const AnalogKeyState analogKeyState);

	// 現在フレームに押されているボタンのビットフラグ
	int GetNowFrameInput() const { return input_nowframe; }
	// 現在フレームで新たに押されたボタンのビットフラグ
	int GetNowFrameNewInput() const { return input_newframe; }

private:
	static constexpr int ANALOGKEY_DEADZONE = 50; // スティック微動以下は無視する閾値

	int input_nowframe;   // 現在フレームで押下中のボタン
	int input_newframe;   // 現在フレームで新規に押されたボタン
	int input_rightkey_x; // 右アナログの水平入力値
	int input_rightkey_z; // 右アナログの垂直入力値
};
