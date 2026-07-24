#include "stdafx.hpp"
#include "Text.hpp"
#include "UiManager.hpp"
#include "EffectCreator.hpp"
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
	if (ObjectAccessor::GetObjectAccessor().GetIsReadyLaser())
	{
		EffectCreator::GetEffectCreator().PlayLoop2D(EffectCreator::EffectType::LaserIcon, VGet(900, 970, 0));
		EffectCreator::GetEffectCreator().SetLoopPosition2D(EffectCreator::EffectType::LaserIcon, VGet(900, 970, 0));
	}
	else
	{
		EffectCreator::GetEffectCreator().StopLoop2D(EffectCreator::EffectType::LaserIcon);
	}
}

void Text::Draw() const
{
	if (ObjectAccessor::GetObjectAccessor().GetInputType() > 0)
	{
		if (ObjectAccessor::GetObjectAccessor().GetIsReadyLaser())
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

	if (ObjectAccessor::GetObjectAccessor().GetIsReadyLaser())
	{
		DrawGraphF(0, 0, graph_handle, true);
		DrawGraphF(0, 0, ready_laser_mouse, true);
		return;
	}
	DrawGraphF(0, 0, graph_handle, true);
	DrawGraphF(0, 0, not_ready_laser_mouse, true);

}