#pragma once

#include "GameObject.hpp"
class Effect;
class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Initialize()override;		//初期化
	void Update()override;      		//更新
	void Draw()override;       		//描画

	// シーン別描画 (特別処理なしのため通常描画呼び出し)
	void DrawTitle() override { Draw(); }
	void DrawGameOver() override { Draw(); }
	void DrawGameClear() override { Draw(); }

	// シーン別更新 (現状特別処理無し)
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};

private:
	// 静的定数.
	static constexpr float SCALE = 0.0125f;		//大きさ
	static constexpr float STAGE_HIGHT = 0.750f; 	//大きさ

};