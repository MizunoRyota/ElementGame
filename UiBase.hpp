#pragma once
class UiBase
{
public:
	UiBase();
	~UiBase();
	void DrawGame();
	void DrawTitle();
	void DrawGameOver();
	void DrawGameClear();
private:
	int titleGraph;
	int target_graph;
};

