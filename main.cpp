#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Camera.hpp"
#include "Skydome.hpp"
#include "Stage.hpp"
#include "Input.hpp"
#include "EnemyBase.hpp"
#include "PlayerBase.hpp"
#include "EffectBase.hpp"
#include "UiBase.hpp"
#include "Shadow.hpp"
#include "BulletManager.hpp"
#include "HitChecker.hpp"
#include "UiManager.hpp"
#include "GameManager.hpp"
#include "Sound.hpp"
enum STATE
{
	STATE_LOAD,			//ロード.
	STATE_INIT,			//初期化.
	STATE_TITLE,		//タイトル.
	STATE_READY,        //準備
	STATE_TUTORIAL,     //準備
	STATE_LESSON,		//ゲームが始まるまでのカウント
	STATE_GAME,			//ゲーム中.
	STATE_READYGAMEOVER,//やられている状態
	STATE_READYCLEAR,	//クリア状態
	STATE_GAMEOVER,		//ゲームオーバー.
	STATE_CLEAR,		//ゲームクリア.
};

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
	std::shared_ptr<GameManager> game_manager = std::make_shared<GameManager>();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::shared_ptr<Input> input = std::make_shared<Input>();
	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
	std::shared_ptr<Skydome> skydome = std::make_shared<Skydome>();
	std::shared_ptr<EnemyBase> enemy_base = std::make_shared<EnemyBase>();
	std::shared_ptr<PlayerBase> player_base = std::make_shared<PlayerBase>();
	std::shared_ptr<EffectBase> effect_base = std::make_shared<EffectBase>();
	std::shared_ptr<UiBase> ui_base = std::make_shared<UiBase>();
	std::shared_ptr<Shadow> shadow = std::make_shared<Shadow>();
	std::shared_ptr<BulletManager>playerbullet_manager = std::make_shared<BulletManager>();
	std::shared_ptr<BulletManager>enemybullet_manager = std::make_shared<BulletManager>();
	std::shared_ptr<HitChecker> hit_checker = std::make_shared<HitChecker>();
	std::shared_ptr<Sound> sound = std::make_shared<Sound>();
	sound->Load();	// サウンドの読み込み

	// 初期化処理
	int game_state = STATE_INIT;	// ゲームの状態を初期化

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		auto prevTime = GetNowHiPerformanceCount();	// 処理が始まる前の時間
		if (game_state == STATE_INIT)
		{
			for (int num = 0; num < 50; num++)
			{
					playerbullet_manager->DeleteBullet(num);
					enemybullet_manager->DeleteBullet(num);

			}
			enemy_base->Initialize();
			player_base->Initialize();
			shadow->Init();
			player_base->SetBulletManager(playerbullet_manager);
			enemy_base->SetBulletManager(enemybullet_manager);
			enemybullet_manager->Initialize();
			playerbullet_manager->Initialize();
			game_state = STATE_TITLE;	// タイトル状態に移行
			ui_base->Initialize();	// UIの初期化
		}
		else if (game_state == STATE_TITLE)
		{
			sound->StopGameOver();
			sound->StopGameClear();
			sound->PlayTitle();
			// マウスカーソル非表示
			SetMouseDispFlag(true);
			// マウスカーソル表示
			SetMouseDispFlag(true);
			shadow->Update();	// シャドウマップの更新
			effect_base->Update(player_base->GetPosition());
			enemy_base->UpdateGameTitle();
			camera->UpdateTitle(enemy_base->GetPosition());

			ClearDrawScreen();
			// 画面を初期化する
			ClearDrawScreen();
			skydome->Draw();
			//シャドウマップの準備
			ShadowMap_DrawSetup(shadow->GetShadowMapHandle());

			stage->Draw();
			player_base->Draw();
			enemy_base->Draw();
			effect_base->DrawEffect();
			ui_base->DrawTitle();
			//シャドウマップへの描画を終了
			ShadowMap_DrawEnd();

			// 描画に使用するシャドウマップを設定
			SetUseShadowMap(0, shadow->GetShadowMapHandle());
			skydome->Draw();
			stage->Draw();
			player_base->Draw();
			enemy_base->Draw();
			effect_base->DrawEffect();
			ui_base->DrawTitle(); // タイトル画面を描画
			// 描画に使用するシャドウマップの設定を解除
			SetUseShadowMap(0, -1);

			ScreenFlip(); // 画面を更新する
			if ((GetMouseInput() & MOUSE_INPUT_LEFT))
			{
				sound->PlayDecide();

				WaitTimer(1000);
				game_state = STATE_READY; // タイトル状態から準備状態に移行
			}
		}
		else if (game_state == STATE_READY)
		{
			enemy_base->InitializeGame(); // 敵の初期化

			game_manager->FadeOutToWhite(1000);

			if (game_manager->GetisWhiteOut())
			{
				ClearDrawScreen();
				WaitTimer(80);
				game_state = STATE_GAME;
			}
		}

		else if (game_state == STATE_GAME)
		{
			sound->StopTitle();
			sound->PlayGame();
			if ((GetMouseInput() & MOUSE_INPUT_LEFT))
			{
				sound->PlaySlash();
			}
			// マウスカーソル非表示
			SetMouseDispFlag(FALSE);
			auto prevTime = GetNowHiPerformanceCount();	// 処理が始まる前の時間
			shadow->Update();	// シャドウマップの更新
			skydome->Update();
			input->Update();
			player_base->Update(*input, *camera);
			enemy_base->Update(player_base->GetPosition(), *stage);
			playerbullet_manager->Update();
			enemybullet_manager->Update();
			for (int num = 0; num < 50; num++)
			{
				if (hit_checker->Update(enemybullet_manager->GetBulletPosition(num), player_base->GetPosition()))
				{
					sound->PlayOnplayer();
					
					player_base->TakeDamage(enemy_base->GetDamageStrength()); // プレイヤーがダメージを受ける
					enemybullet_manager->DeleteBullet(num);
				}
			}
			for (int num = 0; num < 50; num++)
			{
				if (hit_checker->Update(playerbullet_manager->GetBulletPosition(num), enemy_base->GetPosition()))
				{
					sound->PlayOnenemy();

					enemy_base->TakeDamage(enemy_base->GetDamageStrength()); // プレイヤーがダメージを受ける
					playerbullet_manager->DeleteBullet(num);

				}
			}
			camera->Update(player_base->GetPosition());
			ui_base->UpdateGame(player_base->GetHp(), enemy_base->GetHp());
			effect_base->Update(player_base->GetPosition());
			// 画面を初期化する
			ClearDrawScreen();
			skydome->Draw();
			//シャドウマップの準備
			ShadowMap_DrawSetup(shadow->GetShadowMapHandle());

			stage->Draw();
			player_base->Draw();
			enemy_base->Draw();
			effect_base->DrawEffect();

			//シャドウマップへの描画を終了
			ShadowMap_DrawEnd();

			// 描画に使用するシャドウマップを設定
			SetUseShadowMap(0, shadow->GetShadowMapHandle());
			skydome->Draw();
			stage->Draw();
			player_base->Draw();
			enemy_base->Draw();
			effect_base->DrawEffect();
			ui_base->DrawGame();
			// 描画に使用するシャドウマップの設定を解除
			SetUseShadowMap(0, -1);
			ScreenFlip();
			if (player_base->GetHp() <= 0) // プレイヤーのHPが0以下ならゲームオーバー状態へ
			{
				game_state = STATE_GAMEOVER;
			}
			else if (enemy_base->GetHp() <= 0) // 敵のHPが0以下ならクリア状態へ
			{
				game_state = STATE_READYCLEAR;
			}
		}
		else if (game_state == STATE_READYGAMEOVER)
		{
			game_manager->FadeOutToWhite(1000);

			if (game_manager->GetisWhiteOut())
			{
				ClearDrawScreen();
				WaitTimer(80);
				game_state = STATE_GAME;
			}
		}
		else if (game_state == STATE_READYCLEAR)
		{
			game_manager->FadeOutToWhite(1000);

			if (game_manager->GetisWhiteOut())
			{
				ClearDrawScreen();
				WaitTimer(80);
				game_state = STATE_CLEAR;
			}
		}
		else if (game_state == STATE_GAMEOVER)
		{
			sound->StopGame();
			sound->PlayGameOver();
			// マウスカーソル非表示
			SetMouseDispFlag(true);
			// マウスカーソル表示
			SetMouseDispFlag(true);
			shadow->Update();	// シャドウマップの更新
			effect_base->Update(player_base->GetPosition());
			enemy_base->UpdateGameOver();
			camera->UpdateGameOver(enemy_base->GetPosition());

			ClearDrawScreen();
			// 画面を初期化する
			ClearDrawScreen();
			skydome->Draw();
			//シャドウマップの準備
			ShadowMap_DrawSetup(shadow->GetShadowMapHandle());

			stage->Draw();
			player_base->Draw();
			enemy_base->Draw();
			effect_base->DrawEffect();
			ui_base->DrawGameOver();
			//シャドウマップへの描画を終了
			ShadowMap_DrawEnd();

			// 描画に使用するシャドウマップを設定
			SetUseShadowMap(0, shadow->GetShadowMapHandle());
			skydome->Draw();
			stage->Draw();
			player_base->Draw();
			enemy_base->Draw();
			effect_base->DrawEffect();
			ui_base->DrawGameOver(); // タイトル画面を描画
			// 描画に使用するシャドウマップの設定を解除
			SetUseShadowMap(0, -1);

			ScreenFlip(); // 画面を更新する
			if ((GetMouseInput() & MOUSE_INPUT_LEFT))
			{
				WaitTimer(1000);
				sound->PlayDecide();
				game_state = STATE_INIT; // タイトル状態に戻る
			}
		}
		else if (game_state == STATE_CLEAR)
		{
			sound->StopGame();
			sound->PlayGameClear();
			// マウスカーソル表示
			SetMouseDispFlag(true);
			shadow->Update();	// シャドウマップの更新
			effect_base->Update(player_base->GetPosition());
			enemy_base->UpdateGameClear();
			camera->UpdateClear(enemy_base->GetPosition());

			ClearDrawScreen();
			stage->Draw();
			player_base->Draw();
			enemy_base->Draw();
			effect_base->DrawEffect();
			//シャドウマップへの描画を終了
			ShadowMap_DrawEnd();

			// 描画に使用するシャドウマップを設定
			SetUseShadowMap(0, shadow->GetShadowMapHandle());
			skydome->Draw();
			stage->Draw();
			player_base->Draw();
			enemy_base->Draw();
			effect_base->DrawEffect();
			ui_base->DrawGameClear(); // タイトル画面を描画
			// 描画に使用するシャドウマップの設定を解除
			SetUseShadowMap(0, -1);

			ScreenFlip(); // 画面を更新する
			if ((GetMouseInput() & MOUSE_INPUT_LEFT))
			{
				WaitTimer(1000);
				sound->PlayDecide();
				game_state = STATE_INIT; // タイトル状態に戻る
			}
		}

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
