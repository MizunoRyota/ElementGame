#include "Dxlib.h"
#include "UiBase.hpp"

UiBase::UiBase()
	:titleGraph(0)
{
	titleGraph = LoadGraph("data/Texture/Game.png");
}

UiBase::~UiBase()
{
}

void UiBase::DrawTitle()
{
	DrawGraph(0, 0, titleGraph,TRUE);
}
