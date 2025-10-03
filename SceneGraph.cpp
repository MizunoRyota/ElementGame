#include "stdafx.hpp"
#include "SceneGraph.hpp"
#include "UiManager.hpp"

SceneGraph::SceneGraph()
{
	button_pos_y = 0;
	button_isdown = true;

	title_graph = LoadGraph("data/Texture/Title.png");
	titlebutton_graph = LoadGraph("data/Texture/TitleButton.png");

	tutorial_graph = LoadGraph("data/Texture/Tutorial.png");
	tutorialbutton_graph = LoadGraph("data/Texture/TutorialButton.png");

	graph_handle = LoadGraph("data/Texture/Title.png");

	gameclear_graph = LoadGraph("data/Texture/Clear.png");

	gameover_graph = LoadGraph("data/Texture/GameOver.png");

}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::Update()
{
	if (button_pos_y <= 0)
	{
		button_isdown = true;
	}
	else if (button_pos_y >= 25)
	{
		button_isdown = false;

	}
	if (!button_isdown)
	{
		button_pos_y -= UP_SPEED;
	}
	else if (button_isdown)
	{
		button_pos_y += DOWN_SPEED;
	}
}

void SceneGraph::Draw() const
{
	//DrawGraph(0, 0, graph_handle, true);
}
void SceneGraph::DrawTitle() const
{
	DrawGraph(0, 0, title_graph, true);
	DrawGraph(0, button_pos_y, titlebutton_graph, true);
}

void SceneGraph::DrawTutorial() const
{
	DrawGraph(0, 0, tutorial_graph, true);
	DrawGraph(0, button_pos_y, tutorialbutton_graph, true);
}

void SceneGraph::DrawGameOver() const
{
	DrawGraph(0, 0, gameover_graph, true);
	DrawGraph(0, button_pos_y, titlebutton_graph, true);
}
void SceneGraph::DrawGameClear() const
{
	DrawGraph(0, 0, gameclear_graph, true);
	DrawGraph(0, button_pos_y, titlebutton_graph, true);
}