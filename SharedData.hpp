#pragma once
#include <memory>
#include <vector>
#include <string>
//#include "GameObject.hpp"
//#include "CharacterBase.hpp"

class Shadow;
class Input;
class Camera;
class GameObject;
class CharacterBase;
class Stage;
class Skydome;
class Player;
class Enemy;

class SharedData
{
public:
	SharedData();
	~SharedData();

	void AddList(std::shared_ptr<GameObject> obj);

	void InitializeAll();

	void UpdateAll();

	void DrawAll();

	std::shared_ptr<GameObject> FindObject(std::string_view obj);

	std::vector<std::shared_ptr<GameObject>> objects;

	std::shared_ptr<Shadow> shadow = nullptr;
	std::shared_ptr<Input> input = nullptr;
	std::shared_ptr<Camera> camera = nullptr;
	std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<Enemy> enemy = nullptr;
	std::shared_ptr<Stage> stage = nullptr;
	std::shared_ptr<Skydome> skydome = nullptr;
};

