#include "stdafx.hpp"
#include "Text.hpp"
#include "UiManager.hpp"


Text::Text()
{
	graph_handle = LoadGraph("data/Texture/text_game.png");
}

Text::~Text()
{
}

void Text::Update()
{
	//ˆ—‚È‚µ
}

void Text::Draw() const
{
	DrawGraph(0, 0, graph_handle, true);

}