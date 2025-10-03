#pragma once
#include "UiManager.hpp"
class Player;

class TakeDamageUi : public IUiElement
{
public:
	TakeDamageUi(const std::shared_ptr<Player>& player);
	~TakeDamageUi();
	void UpdateTitle() override{};
	void Update() override;      // 値更新
	 void UpdateGameClear()override{};
	 void UpdateGameOver()override{};
	void Draw() const override;
	void DrawTitle() const override {};  // 描画
	void DrawTutorial() const override {};
	void DrawGameClear() const override {};  // 描画
	void DrawGameOver() const override {};  // 描画
private:
	int text_graph;
	float alpha_ = 0.0f;               // 0.0~255.0 使用
	float fade_in_speed_ = 25.0f;      // 被弾時上昇速度
	float fade_out_speed_ = 5.0f;      // 未被弾時減衰速度
	int recent_invincible_prev_ = 0;   // 前フレームの無敵タイマー
	std::weak_ptr<Player> player_;     // プレイヤー参照
};
