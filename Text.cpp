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
	DrawGraphF(0, 0, graph_handle, true);
}