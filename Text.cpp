#include "stdafx.hpp"
#include "Text.hpp"
#include "UiManager.hpp"
#include "ObjectAccessor.hpp"

Text::Text()
{
	graph_handle = LoadGraph("data/Texture/TextGame.png");
	game_controller = LoadGraph("data/Texture/TextGameController.png");
	ready_laser_mouse = LoadGraph("data/Texture/ReadyLaserMouse.png");
	ready_laser_controller = LoadGraph("data/Texture/ReadyLaserController.png");
	not_ready_laser_mouse = LoadGraph("data/Texture/NotReadyLaserMouse.png");
	not_ready_laser_controller = LoadGraph("data/Texture/NotReadyLaserController.png");
}

Text::~Text()
{
	DeleteGraph(graph_handle);
}

void Text::Update()
{
	//ˆ—‚È‚µ
}

void Text::Draw() const
{
	if (ObjectAccessor::GetObjectAccessor().GetInputType() > 0)
	{
		if (ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak())
		{
			DrawGraphF(0, 0, game_controller, true);
			DrawGraphF(0, 0, ready_laser_controller, true);
			return;
		}
		else
		{
			DrawGraphF(0, 0, game_controller, true);
			DrawGraphF(0, 0, not_ready_laser_controller, true);
		}
		return;
	}

	if (ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak())
	{
		DrawGraphF(0, 0, graph_handle, true);
		DrawGraphF(0, 0, ready_laser_mouse, true);
		return;
	}
	DrawGraphF(0, 0, graph_handle, true);
	DrawGraphF(0, 0, not_ready_laser_mouse, true);

}