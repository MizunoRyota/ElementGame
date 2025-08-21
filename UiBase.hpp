#pragma once
class UiBase
{
public:
	UiBase();
	~UiBase();
	void Initialize();
	void UpdateGame(int playerhp,int enemyhp);
	void DrawTitle();
	void DrawGame();
	void DrawTarget();
	void DrawGameOver();
	void DrawGameClear();
private:
	int titleGraph;
	int target_graph;
	int gameover_graph;
	int gameclear_graph;
	int game_graph;
	int playerhpfull_graph;
	int playerhpempty_graph;
	int enemyhpfull_graph;
	int enemyhpempty_graph;
	int player_hpgaugewidth;
	int enemy_hpgaugewidth;

};

