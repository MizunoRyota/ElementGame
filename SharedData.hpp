#pragma once

// SharedData:
// ゲーム全体で共有する各種インスタンス（入力/カメラ/プレイヤー等）と、
// シーンごとに更新・描画される `GameObject` リストをまとめて管理するクラス。
//
// 役割:
// - Title / Tutorial / Game / GameOver / GameClear などのシーン単位で
//   オブジェクトの更新・描画の呼び分けを行う
// - 影描画用の別リスト（`objects_shadow_ready`）を保持し、影生成の準備を行う
// - 主要システムの共有インスタンスを保持し、生成・初期化の起点になる

class Shadow;
class Input;
class Camera;
class GameObject;
class CharacterBase;
class Stage;
class Skydome;
class Player;
class Enemy;
class UiManager;
class Crystal;

class SharedData
{
public:
	SharedData();
	~SharedData();

	// Gameシーンで更新・描画するオブジェクトを追加する
	void AddGameList(std::shared_ptr<GameObject> obj);

	// 影描画の対象（影を落とす/影を付ける）オブジェクトを追加する
	void AddShadowReady(std::shared_ptr<GameObject> obj);

	// 登録済みオブジェクトや共有インスタンスの初期化をまとめて行う
	void InitializeAll();

	// Titleシーンの更新
	void UpdateTitle();

	// Tutorialシーンの更新
	void UpdateTutorial();

	// Gameシーンの更新
	void UpdateGame();

	// GameOverシーンの更新
	void UpdateGameOver();

	// GameClearシーンの更新
	void UpdateGameClear();

	// Titleシーンの描画
	void DrawTitle();

	// Tutorialシーンの描画
	void DrawTutorial();

	// Gameシーン（通常ゲーム中）の描画
	void DrawAll();

	// GameClearシーンの描画
	void DrawGameClear();

	// GameOverシーンの描画
	void DrawGameOver();

	// 影描画の準備/処理（影対象リストを使う描画など）
	void DrawShadowReady();

	// 文字列識別子などからオブジェクトを検索して取得する
	std::shared_ptr<GameObject> FindObject(std::string_view obj);

	// --- オブジェクトリスト ---
	// ゲーム内で動く（主にGameシーンで更新・描画される）リスト
	std::vector<std::shared_ptr<GameObject>> objects_game;

	// 影を付ける（影描画に利用する）リスト
	std::vector<std::shared_ptr<GameObject>> objects_shadow_ready;

	// --- 共有インスタンス（シングルトン的に全体で使い回す想定） ---
	// ※ここでは所有権を `SharedData` が保持し、各シーン/オブジェクトから参照される
	std::shared_ptr<Shadow> shadow;		// 影
	std::shared_ptr<Input> input;		// 入力
	std::shared_ptr<Camera> camera;		// カメラ
	std::shared_ptr<Player> player;		// プレイヤー
	std::shared_ptr<Enemy> enemy;		// 敵
	std::shared_ptr<Stage> stage;		// ステージ
	std::shared_ptr<Skydome> skydome;	// スカイドーム
	std::shared_ptr<UiManager> ui;		// UI
	std::shared_ptr<Crystal> crystal;	// クリスタル

};