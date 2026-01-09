#include "stdafx.hpp"
#include "SceneGraph.hpp"
#include "UiManager.hpp"
#include "ObjectAccessor.hpp"
SceneGraph::SceneGraph()
{
	button_pos_y = 0;
	button_is_down = true;

	title_graph = LoadGraph("data/Texture/Title.png");
	a_button_graph = LoadGraph("data/Texture/TitleAButton.png");

	tutorial_graph = LoadGraph("data/Texture/Tutorial.png");
	tutorialbutton_graph = LoadGraph("data/Texture/TutorialButton.png");

	graph_handle = LoadGraph("data/Texture/Title.png");

	gameclear_graph = LoadGraph("data/Texture/Clear.png");

	gameover_graph = LoadGraph("data/Texture/GameOver.png");

}

SceneGraph::~SceneGraph()
{
	DeleteGraph(title_graph);
	DeleteGraph(a_button_graph);
	DeleteGraph(tutorial_graph);
	DeleteGraph(tutorialbutton_graph);
	DeleteGraph(graph_handle);
	DeleteGraph(gameclear_graph);
	DeleteGraph(gameover_graph);
}

void SceneGraph::Update()
{
	if (button_pos_y <= 0)
	{
		button_is_down = true;
	}
	else if (button_pos_y >= 25)
	{
		button_is_down = false;

	}
	if (!button_is_down)
	{
		button_pos_y -= UP_SPEED;
	}
	else if (button_is_down)
	{
		button_pos_y += DOWN_SPEED;
	}
}

void SceneGraph::Draw() const
{
	//DrawGraphF(0, 0, graph_handle, true);
}
void SceneGraph::DrawTitle() const
{
	DrawGraphF(0, 0, title_graph, true);
	if (ObjectAccessor::GetObjectAccessor().GetInputType() > 0)
	{
		DrawGraphF(0, button_pos_y, a_button_graph, true);
	}
	else
	{
		DrawGraphF(0, button_pos_y, tutorialbutton_graph, true);
	}
}

void SceneGraph::DrawTutorial() const
{
	DrawGraphF(0, 0, tutorial_graph, true);
	if (ObjectAccessor::GetObjectAccessor().GetInputType() > 0)
	{
		DrawGraphF(0, button_pos_y, a_button_graph, true);
	}
	else
	{
		DrawGraphF(0, button_pos_y, tutorialbutton_graph, true);
	}
}

void SceneGraph::DrawGameOver() const
{
	DrawGraphF(0, 0, gameover_graph, true);
	if (ObjectAccessor::GetObjectAccessor().GetInputType() > 0)
	{
		DrawGraphF(0, button_pos_y, a_button_graph, true);
	}
	else
	{
		DrawGraphF(0, button_pos_y, tutorialbutton_graph, true);
	}
}
void SceneGraph::DrawGameClear() const
{
	DrawGraphF(0, 0, gameclear_graph, true);
	if (ObjectAccessor::GetObjectAccessor().GetInputType() > 0)
	{
		DrawGraphF(0, button_pos_y, a_button_graph, true);
	}
	else
	{
		DrawGraphF(0, button_pos_y, tutorialbutton_graph, true);
	}
}