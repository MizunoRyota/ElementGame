#include "stdafx.hpp"
#include "Dxlib.h"
#include "EffekseerForDXLib.h"
#include "TitleScene.hpp"
#include "Tutorial.hpp"
#include "GameScene.hpp"
#include "GameOverScene.hpp"
#include "GameClearScene.hpp"
#include "SceneManager.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// 画面モードのセット
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	ChangeWindowMode(TRUE);

	// DXライブラリを初期化する。
	if (DxLib_Init() == -1) return -1;

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う
	srand((unsigned)time(NULL));	//ランダム抽選おまじない

	std::shared_ptr<SceneManager> scene_manager = std::make_shared<SceneManager>();

	scene_manager->Add<TitleScene>("TitleScene");
	scene_manager->Add<TutorialScene>("TutorialScene");
	scene_manager->Add<GameScene>("GameScene");
	scene_manager->Add<GameOverScene>("GameOverScene");
	scene_manager->Add<GameClearScene>("GameClearScene");

	bool debugPauseFlag = false;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// ぼたんおしたら
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// ぼたんおしたら
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		auto prevTime = GetNowHiPerformanceCount();	// 処理が始まる前の時間

		scene_manager->Update();

		scene_manager->Draw();

		// 差を求めて、1回の画面更新が1/60秒になるようにwhileループ回して待つ
		auto afterTime = GetNowHiPerformanceCount(); // 処理が終わった後の時間
		while (afterTime - prevTime < 16667)
		{
			afterTime = GetNowHiPerformanceCount();
		}
	}

	// Effekseerを終了する。
	Effkseer_End();
	// 後始末
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}