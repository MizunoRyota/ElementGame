#include "stdafx.hpp"
#include "SharedData.hpp"
#include "Shadow.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Effect.hpp"
#include "Stage.hpp"
#include "Skydome.hpp"
#include "Enemy.hpp"

SharedData::SharedData()
{
	stage = std::make_shared<Stage>();
	shadow = std::make_shared<Shadow>();
	input = std::make_shared<Input>();
	camera = std::make_shared<Camera>();
	player = std::make_shared<Player>();
	skydome = std::make_shared<Skydome>();
	enemy = std::make_shared<Enemy>();
	camera->SetPlayer(player);
	enemy->SetPlayer(player);
	player->SetCamera(camera);
	player->SetInput(input);
	AddList(skydome);
	AddList(stage);
	AddList(shadow);
	AddList(input);
	AddList(player);
	AddList(enemy);
	AddList(camera);
}

SharedData::~SharedData()
{
}

/// <summary>
/// リストに追加
/// </summary>
/// <param name="obj"></param>
void SharedData::AddList(std::shared_ptr<GameObject> obj)
{
	objects.push_back(obj);
}
/// <summary>
/// リストの中身を初期化
/// </summary>
void SharedData::InitializeAll()
{
	for (auto object : objects)
	{
		object->Initialize();
	}
}
/// <summary>
/// リストの中身を更新
/// </summary>
void SharedData::UpdateAll()
{
	for (auto object : objects)
	{
		object->Update();
	}
}
/// <summary>
/// リストの中身を描画
/// </summary>
void SharedData::DrawAll()
{
	for (auto object : objects)
	{
		object->Draw();
	}
}
/// <summary>
/// リストの中身を探して返す
/// </summary>
/// <param name="obj_name"></param>
/// <returns></returns>
std::shared_ptr<GameObject> SharedData::FindObject(std::string_view obj_name)
{
	for (auto object : objects)
	{
		if (object->GetNameTag() == obj_name)
		{
			return object;
		}
	}
	return nullptr;
}