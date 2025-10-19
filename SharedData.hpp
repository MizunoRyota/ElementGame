#pragma once

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

	void AddTitleList(std::shared_ptr<GameObject> obj);

	void AddGameList(std::shared_ptr<GameObject> obj);

	void AddGameClearList(std::shared_ptr<GameObject> obj);

	void AddGameOverList(std::shared_ptr<GameObject> obj);

	void AddShadowReady(std::shared_ptr<GameObject> obj);

	void InitializeAll();

	void UpdateTitle();

	void UpdateTutorial();

	void UpdateGame();

	void UpdateGameOver();

	void UpdateGameClear();

	void DrawTitle();

	void DrawTutorial();

	void DrawAll();

	void DrawGameClear();

	void DrawGameOver();

	void DrawShadowReady();

	std::shared_ptr<GameObject> FindObject(std::string_view obj);

	std::vector<std::shared_ptr<GameObject>> objects_title;
	std::vector<std::shared_ptr<GameObject>> objects_game;
	std::vector<std::shared_ptr<GameObject>> objects_gameover;
	std::vector<std::shared_ptr<GameObject>> objects_gameclear;


	std::vector<std::shared_ptr<GameObject>> objects_shadow_ready;


	std::shared_ptr<Shadow> shadow = nullptr;
	std::shared_ptr<Input> input = nullptr;
	std::shared_ptr<Camera> camera = nullptr;
	std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<Enemy> enemy = nullptr;
	std::shared_ptr<Stage> stage = nullptr;
	std::shared_ptr<Skydome> skydome = nullptr;
	std::shared_ptr<UiManager> ui = nullptr; // HPバー描画用
	std::shared_ptr<Crystal> crystal = nullptr; // チャージ中クリスタル
	
};

