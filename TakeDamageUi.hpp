#pragma once
#include "UiManager.hpp"
class Player;

// 被ダメージ時のUI（赤フラッシュ等）
class TakeDamageUi : public IUiElement
{
public:
	TakeDamageUi(const std::shared_ptr<Player>& player);
	~TakeDamageUi();
	void UpdateTitle() override{};
	void Update() override;      // 値更新
	 void UpdateGameClear()override{};
	 void UpdateGameOver()override{};
	void Draw() const override;  // 描画
	void DrawTitle() const override {};  // 描画
	void DrawTutorial() const override {};
	void DrawGameClear() const override {};  // 描画
	void DrawGameOver() const override {};  // 描画
private:
	static constexpr int ALPHA_MAX = 255;
	int text_graph;
	float alpha = 0.0f;               // 0.0~255.0 使用
	float fade_in_speed_ = 25.0f;      // フェードイン速度
	float fade_out_speed = 5.0f;      // フェードアウト速度
	int recent_invincible_prev_ = 0;   // 前フレームの無敵タイマー
	std::weak_ptr<Player> player_;     // プレイヤー参照
};
