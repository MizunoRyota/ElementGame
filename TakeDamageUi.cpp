#include "stdafx.hpp"
#include "TakeDamageUi.hpp"
#include "UiManager.hpp"
#include "Player.hpp"
#include "CharacterBase.hpp"

TakeDamageUi::TakeDamageUi(const std::shared_ptr<Player>& player)
	:player_(player)
{
	graph_handle = LoadGraph("data/Texture/take_damage.png");
}

TakeDamageUi::~TakeDamageUi()
{
}

void TakeDamageUi::Update()
{
	// プレイヤーが設定されていなければフェードアウト
	bool tookDamageThisFrame = false;
	if (auto p = player_.lock())
	{
		// CharacterBase に無敵タイマー取得 API がなければ必要に応じて追加する想定
		// ここでは被弾直後は IsInvincible() が true になる前提で、前フレームとの差で被弾検出
		// 簡易: HP 減少を検出(要: 前フレームHP保持) -> 現状その仕組み無いので無敵残り時間を使う案
		// 仮: IsInvincible() が true かつ 前フレームで false だったら被弾
		bool nowInv = p->IsInvincible();
		bool prevInv = (recent_invincible_prev_ > 0);
		if (nowInv && !prevInv)
		{
			tookDamageThisFrame = true;
		}

		// 無敵残り時間の概念を直接参照できないので、フラグ遷移のみを追跡するために疑似的に1/0管理
		recent_invincible_prev_ = nowInv ? 1 : 0;
	}
	else
	{
		recent_invincible_prev_ = 0;
	}

	if (tookDamageThisFrame)
	{
		alpha_ = 255.0f;
	}
	else
	{
		alpha_ -= fade_out_speed_;
		if (alpha_ < 0.0f) alpha_ = 0.0f;
	}
}

void TakeDamageUi::Draw() const
{
	if (alpha_ <= 0.0f) return; // 完全に透明なら描画不要
	int a = static_cast<int>(alpha_);
	if (a > 255) a = 255; if (a < 0) a = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	DrawGraph(0, 0, graph_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}