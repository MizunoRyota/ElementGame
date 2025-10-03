#pragma once

#include "AnimationData.hpp"
class AnimaterBase
{
public:
	AnimaterBase(int anim_modelhandle);
	virtual~AnimaterBase();
public:

	virtual void InitializeAnimationData() = 0; // 各派生のモーションテーブル初期化
	virtual void Update() = 0;                  // フレーム更新(派生)
	void ChangeMotion(AnimationState nextstate); // モーション遷移要求
	void UpdateAnimation();                     // 時間経過と再生
	virtual void SwitchAnimation() = 0;         // ステートから次モーションを決定

	const float& GetAmimFrame() const { return anim_currentstate.anim_nowtime; } // 現在フレーム時間
	const bool& GetAmimIsEnd() const { return anim_isend; }                      // 再生完了か

protected:
	static constexpr float ANIM_BLEND_SPEED = 0.1f; // ブレンド補間速度

	float anim_blendrate;        // 前後モーション間現在ブレンド率
	float anim_nowframe;         // 現在再生フレーム(整数カウント用)
	bool  anim_isend;            // 現モーション終了フラグ
	int   anim_modelhandle;      // モデルハンドル
	AnimationState anim_prevstate;    // 直前ステート
	AnimationState anim_currentstate; // 現在ステート
	std::unordered_map<int, AnimationState> animation_data; // 登録アニメーション辞書
};