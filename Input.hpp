#pragma once

#include "GameObject.hpp" // GameObject クラスの定義をインクルード

class GameObject;
	/// <summary>
	/// 入力
	/// </summary>
class Input : public GameObject
{
public:

	/// <summary>
	/// アナログキーのステート
	/// </summary>
	enum AnalogKeyState
	{
		AnalogRight = 1,    //右
		AnalogLeft = 2,     //左
		AnalogUp = 3,       //上
		AnalogDown = 4,     //下
	};
	//キーの種類
	enum KeyKinds
	{
		Move = 0,	//移動キーのどれか
		Left = 1,	//右
		Right = 2,  //左
		Up = 3,		//上
		Down = 4,	//下
		Space = 5,  //スペース
		LB = 6,		//左側の上のボタン
		LT = 7,		//左側の下側のボタン
		RB = 8,		//右側の上のボタン
		RT = 9,		//右側の下のボタン
		X = 10,
		Y = 11,
		A = 12,
		B = 13,
		LeftStick = 14,  //左スティック押し込み
		None = 15,  //使用しないキーまたは未入力
	};
	Input();
	~Input();

	void Initialize()override;
	void Update()override;
	void Draw()override;

	// シーン別描画 (入力は描画不要のため空)
	void DrawTitle() override {};
	void DrawGameOver() override {};
	void DrawGameClear() override {};

	// シーン別更新 (入力状態は常に収集する想定なので空)
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};

	bool IsInputAnalogKey(const AnalogKeyState analogKeyState);
	int GetNowFrameInput() const { return input_nowframe; }
	int GetNowFrameNewInput() const { return input_newframe; }

private:

	static constexpr int ANALOGKEY_DEADZONE = 50;     // スティックがこれ以下なら無反応にする閾値

	int		input_nowframe; 			// 現在のフレームで押されているボタン
	int		input_newframe; 		// 現在のフレームで新たに押されたボタン
	int     input_rightkey_x; 		// 右のアナログキーの横方向の値
	int     input_rightkey_z; 		// 右のアナログキーの縦方向の値
};
