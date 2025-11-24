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

    //それぞれのキー名前とDxライブラリ上での識別番号をセットにする
    //input_tag.insert(std::make_pair(Move,       MoveKeyIndex));
    input_tag.insert(std::make_pair(Space,      PAD_INPUT_10));
    input_tag.insert(std::make_pair(Left,       PAD_INPUT_LEFT));
    input_tag.insert(std::make_pair(Right,      PAD_INPUT_RIGHT));
    input_tag.insert(std::make_pair(Up,         PAD_INPUT_UP));
    input_tag.insert(std::make_pair(Down,       PAD_INPUT_DOWN));
    input_tag.insert(std::make_pair(X,          PAD_INPUT_1));
    input_tag.insert(std::make_pair(Y,          PAD_INPUT_2));
    input_tag.insert(std::make_pair(A,          PAD_INPUT_3));
    input_tag.insert(std::make_pair(B,          PAD_INPUT_4));
    input_tag.insert(std::make_pair(LB,         PAD_INPUT_5));
    input_tag.insert(std::make_pair(RB,         PAD_INPUT_6));
    input_tag.insert(std::make_pair(LT,         PAD_INPUT_7));
    input_tag.insert(std::make_pair(RT,         PAD_INPUT_8));
    input_tag.insert(std::make_pair(LeftStick,  PAD_INPUT_9));

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
    printfDx("%d", input_nowframe);
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