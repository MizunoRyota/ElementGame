#include "stdafx.hpp"
#include "Text.hpp"
#include "UiManager.hpp"
#include "ObjectAccessor.hpp"

Text::Text()
{
	laser_is_ready = false;
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
	if (ObjectAccessor::GetObjectAccessor().GetCrystalIsBreak())
	{
		laser_is_ready = true;
	}

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && laser_is_ready && ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() != PlayerStateKind::STATE_ATTACK
		|| ObjectAccessor::GetObjectAccessor().GetIsInputBottunY() && laser_is_ready && ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() != PlayerStateKind::STATE_ATTACK
		|| ObjectAccessor::GetObjectAccessor().GetPlayerStateKind() == PlayerStateKind::STATE_LASER)
	{
		laser_is_ready = false;
	}


}

void Text::Draw() const
{
	if (ObjectAccessor::GetObjectAccessor().GetInputType() > 0)
	{
		if (laser_is_ready)
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

	if (laser_is_ready)
	{
		DrawGraphF(0, 0, graph_handle, true);
		DrawGraphF(0, 0, ready_laser_mouse, true);
		return;
	}
	DrawGraphF(0, 0, graph_handle, true);
	DrawGraphF(0, 0, not_ready_laser_mouse, true);

}