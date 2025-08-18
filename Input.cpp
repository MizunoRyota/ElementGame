#include "DxLib.h"
#include "Input.hpp"

/// <summary>
/// コンストラクタ
/// </summary>
Input::Input()
    : nowFrameInput(0)
    , nowFrameNewInput(0)
{
    // 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Input::~Input()
{
    // 処理なし
}

/// <summary>
/// 更新
/// </summary>
void Input::Update()
{
    // ひとつ前のフレームの入力を変数にとっておく
    int Old = nowFrameInput;
    // 現在の入力状態を取得
    nowFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    clsDx();
    //printfDx("%d", nowFrameInput);
    // 今のフレームで新たに押されたボタンのビットだけ立っている値を nowFrameNewInput に代入する
    nowFrameNewInput = nowFrameInput & ~Old;
}

bool Input::IsInputAnalogKey(const AnalogKeyState analogKeyState)
{
    // アナログキーの縦横の入力値を用意
    int inputX = 0;
    int inputY = 0;

    // 入力されているか
    bool isInput = false;

    // それぞれの入力をチェック
    GetJoypadAnalogInputRight(&inputX, &inputY, DX_INPUT_PAD1);

    // どのアナログキーをチェックしたいのかをみてそれが倒されているかを見る
    switch (analogKeyState)
    {
    case Right:
        if (inputX > AnalogKeyDeadZone)
        {
            isInput = true;
        }
        break;
    case Left:
        if (inputX < -AnalogKeyDeadZone)
        {
            isInput = true;
        }
        break;
    case Up:
        if (inputY < -AnalogKeyDeadZone)
        {
            isInput = true;
        }
        break;
    case Down:
        if (inputY > AnalogKeyDeadZone)
        {
            isInput = true;
        }
        break;
    default:
        break;
    }

    return isInput;
}