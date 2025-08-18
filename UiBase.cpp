#include "Dxlib.h"
#include "UiBase.hpp"

UiBase::UiBase()
	:titleGraph(0)
	,target_graph(0)
{
	titleGraph = LoadGraph("data/Texture/Game.png");
	target_graph = LoadGraph("data/Texture/Target.png");

}

UiBase::~UiBase()
{
}

void UiBase::DrawTitle()
{
	DrawGraph(0, 0, titleGraph,TRUE);
	DrawGraph(0, 0, target_graph, TRUE);

}
