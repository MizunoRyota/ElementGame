#pragma once

/// <summary>
/// 入力
/// </summary>
class Input
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
		LB = 6,		//左上の手前のボタン
		LT = 7,		//左上の奥側のボタン
		RB = 8,		//右上の手前のボタン
		RT = 9,		//右奥側のボタン
		X = 10,
		Y = 11,
		A = 12,
		B = 13,
		LeftStick = 14,  //左スティック押し込み
		None = 15,  //使用しないキーもしくは押されていない
	};
	Input();
	~Input();

	void	Update();
	bool IsInputAnalogKey(const AnalogKeyState analogKeyState);
	int GetNowFrameInput() const { return nowFrameInput; }
	int GetNowFrameNewInput() const { return nowFrameNewInput; }

private:

	static constexpr int AnalogKeyDeadZone = 50;     // スティックを倒してもすぐ反応しない領域

	int		nowFrameInput;				// 現在のフレームで押されているボタン
	int		nowFrameNewInput;			// 現在のフレームで新たに押されたボタン
	int     rightAnalogKeyX;			// 右のアナログキーの横方向の状態
	int     rightAnalogKeyY;			// 右のアナログキーの縦方向の状態
};
