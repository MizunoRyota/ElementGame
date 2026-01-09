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
	DeleteGraph(graph_handle);
}

void TakeDamageUi::Update()
{
	// プレイヤーが設定されていなければフェードアウト
	bool tookDamageThisFrame = false;
	if (auto p = player_.lock())
	{
		// IsInvincible() が true かつ 前フレームで false だったら被弾
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
		alpha = ALPHA_MAX;
	}
	else
	{
		alpha -= fade_out_speed;
		if (alpha < 0.0f) alpha = 0.0f;
	}
}

void TakeDamageUi::Draw() const
{
	if (alpha <= 0.0f) return; // 完全に透明なら描画不要
	int blendParamater = static_cast<int>(alpha);
	if (blendParamater > ALPHA_MAX) blendParamater = ALPHA_MAX; if (blendParamater < 0) blendParamater = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blendParamater);
	DrawGraphF(0, 0, graph_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}