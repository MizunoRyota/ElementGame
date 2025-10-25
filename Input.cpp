#include "stdafx.hpp"

#include "GameObject.hpp"
#include "Input.hpp"

/// <summary>
/// コンストラクタ
/// </summary>
Input::Input()
{
    input_nowframe = 0;
    input_newframe = 0;
    obj_name = "Input";

}

/// <summary>
/// デストラクタ
/// </summary>
Input::~Input()
{
    // 処理なし
}

void Input::Initialize()
{ }

/// <summary>
/// 更新
/// </summary>
void Input::Update()
{
    // ひとつ前のフレームの入力を変数にとっておく
    int inputOld = input_nowframe;
    // 現在の入力状態を取得
    input_nowframe = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    clsDx();
    //printfDx("%d", input_nowframe);
    // 今のフレームで新たに押されたボタンのビットだけ立っている値を input_newframe に代入する
    input_newframe = input_nowframe & ~inputOld;
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
        if (inputX > ANALOGKEY_DEADZONE)
        {
            isInput = true;
        }
        break;
    case Left:
        if (inputX < -ANALOGKEY_DEADZONE)
        {
            isInput = true;
        }
        break;
    case Up:
        if (inputY < -ANALOGKEY_DEADZONE)
        {
            isInput = true;
        }
        break;
    case Down:
        if (inputY > ANALOGKEY_DEADZONE)
        {
            isInput = true;
        }
        break;
    default:
        break;
    }

    return isInput;
}

void Input::Draw()
{

}