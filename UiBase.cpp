#include "Dxlib.h"
#include "UiBase.hpp"

UiBase::UiBase()
	:titleGraph(0)
	, target_graph(0)
	, player_hpgaugewidth(600)
{
	titleGraph = LoadGraph("data/Texture/Title.png");
	target_graph = LoadGraph("data/Texture/Target.png");
	gameover_graph = LoadGraph("data/Texture/GameOver.png");
	gameclear_graph = LoadGraph("data/Texture/Clear.png");
	game_graph = LoadGraph("data/Texture/Game.png");
	playerhpempty_graph = LoadGraph("data/Texture/PlayerHpEmpty.png");
	playerhpfull_graph = LoadGraph("data/Texture/PlayerHpFull.png");
	enemyhpempty_graph = LoadGraph("data/Texture/EnemyHpEmpty.png");
	enemyhpfull_graph = LoadGraph("data/Texture/EnemyHpFull.png");
}

UiBase::~UiBase()
{
}

void UiBase::Initialize()
{
	// ゲーム画面の初期化
	player_hpgaugewidth = 600; // 初期値を設定
}

void UiBase::UpdateGame(int playerhp, int enemyhp)
{

	//if (playerhp == 90 && player_hpgaugewidth >= 540)
	//{
	//	player_hpgaugewidth -= 2;
	//}
	//else if (playerhp == 80 && player_hpgaugewidth >= 480)
	//{
	//	player_hpgaugewidth -= 2;
	//}
	//else if (playerhp == 70 && player_hpgaugewidth >= 420)
	//{
	//	player_hpgaugewidth -= 2;
	//}
	//else if (playerhp == 60 && player_hpgaugewidth >= 360)
	//{
	//	player_hpgaugewidth -= 2;
	//}
	if (playerhp == 50 && player_hpgaugewidth >= 480)
	{
		player_hpgaugewidth -= 2;
	}
	else if (playerhp == 40 && player_hpgaugewidth >= 360)
	{
		player_hpgaugewidth -= 2;
	}
	else if (playerhp == 30 && player_hpgaugewidth >= 280)
	{
		player_hpgaugewidth -= 2;
	}
	else if (playerhp == 10 && player_hpgaugewidth >= 120)
	{
		player_hpgaugewidth -= 2;
	}

}

void UiBase::DrawTitle()
{
	DrawGraph(0, 0, titleGraph,TRUE);
}

void UiBase::DrawGame()
{
	// テクスチャの描画
	DrawRectGraph(0, 0, 0, 0,1920, 1080, playerhpempty_graph, TRUE, FALSE);
	DrawRectGraph(0, 0, 0, 0, player_hpgaugewidth, 1080, playerhpfull_graph, TRUE, FALSE);
	DrawGraph(0, 0, game_graph, TRUE);
	DrawTarget();
}

void UiBase::DrawTarget()
{
	DrawGraph(0, 0, target_graph, TRUE);
}

void UiBase::DrawGameOver()
{
	DrawGraph(0, 0, gameover_graph, TRUE);
}

void UiBase::DrawGameClear()
{
	DrawGraph(0, 0, gameclear_graph, TRUE);
}