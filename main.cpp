#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Camera.hpp"
#include "Skydome.hpp"
#include "Stage.hpp"
#include "Input.hpp"
#include "EnemyBase.hpp"
#include "PlayerBase.hpp"
#include"EffectBase.hpp"
#include "UiBase.hpp"
#include "Shadow.hpp"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 画面モードのセット
	SetGraphMode(1920, 1080, 32);
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

	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::shared_ptr<Input> input = std::make_shared<Input>();
	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
	std::shared_ptr<Skydome> skydome = std::make_shared<Skydome>();
	std::shared_ptr<EnemyBase> enemybase = std::make_shared<EnemyBase>();
	std::shared_ptr<PlayerBase> player_base = std::make_shared<PlayerBase>();
	std::shared_ptr<EffectBase> effect_base = std::make_shared<EffectBase>();
	std::shared_ptr<UiBase> ui_base = std::make_shared<UiBase>();
	std::shared_ptr<Shadow> shadow = std::make_shared<Shadow>();

	enemybase->Initialize();
	shadow->Init();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{


		// マウスカーソル非表示
		SetMouseDispFlag(FALSE);
		auto prevTime = GetNowHiPerformanceCount();	// 処理が始まる前の時間
		shadow->Update();	// シャドウマップの更新
		skydome->Update();
		input->Update();
		player_base->Update(*input, *camera);
		enemybase->Update(player_base->GetPosition(), *stage);
		camera->Update(player_base->GetPosition());
		effect_base->Update(player_base->GetPosition());
		// 画面を初期化する
		ClearDrawScreen();
		skydome->Draw();
		//シャドウマップの準備
		ShadowMap_DrawSetup(shadow->GetShadowMapHandle());

		stage->Draw();
		player_base->Draw();
		enemybase->Draw();
		effect_base->DrawEffect();
		ui_base->DrawTitle();
		//シャドウマップへの描画を終了
		ShadowMap_DrawEnd();

		// 描画に使用するシャドウマップを設定
		SetUseShadowMap(0, shadow->GetShadowMapHandle());
		skydome->Draw();
		stage->Draw();
		player_base->Draw();
		enemybase->Draw();
		effect_base->DrawEffect();
		ui_base->DrawTitle();
		// 描画に使用するシャドウマップの設定を解除
		SetUseShadowMap(0, -1);
		ScreenFlip();
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