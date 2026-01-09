#include "stdafx.hpp"
#include "reticle.hpp"
#include "UiManager.hpp"

Reticle::Reticle()
{
	graph_handle = LoadGraph("data/Texture/reticle.png");
}

Reticle::~Reticle()
{
	DeleteGraph(graph_handle);

}

void Reticle::Update()
{
	//èàóùÇ»Çµ
}

void Reticle::Draw() const
{
	DrawGraphF(0, 0, graph_handle, true);
}