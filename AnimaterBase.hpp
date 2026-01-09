#pragma once

#include "AnimationData.hpp"

// アニメーション制御の共通基底クラス。
// モデルに対して「どのアニメをどの速度で、どうブレンドして再生するか」を管理します。
// 派生クラスでゲーム固有のステートに応じてアニメを切り替えます。
class AnimaterBase
{
public:
    // モデルハンドルを受け取り初期化
    // anim_modelhandle: モデルのハンドル（DxLib 等）
    AnimaterBase(int anim_modelhandle);
    virtual ~AnimaterBase();

public:
    // 各派生クラスでアニメーションデータ(テーブル)を登録
    virtual void InitializeAnimationData() = 0;

    // 毎フレーム更新（派生で必要な処理を行う）
    virtual void Update() = 0;

    // 次のアニメーションへ切り替え
    // nextstate: 切り替え先のアニメーション状態
    void ChangeMotion(AnimationState nextstate);

    // アニメーションの時間進行・ブレンド・再生終了判定
    void UpdateAnimation();

    // ゲーム内ステートに応じて再生中のアニメを切り替える（派生実装）
    virtual void SwitchAnimation() = 0;

    // 現在の再生フレームを取得
    const float& GetAnimationFrame() const { return anim_currentstate.anim_nowtime; }

    // 現在のアニメが終了したか
    const bool& GetAmimIsEnd() const { return anim_is_end; }

protected:
    // ブレンドスピード。値が大きいほど即座、小さいほどゆっくり切替
    static constexpr float ANIM_BLEND_SPEED = 0.1f;

    float anim_blendrate;        // 現在のブレンド率（0: 前アニメ, 1: 現アニメ）
    float anim_nowframe;         // 現在の再生フレーム（カウンタ用途）
    bool  anim_is_end;           // 再生終了フラグ
    int   anim_modelhandle;      // モデルのハンドル

    AnimationState anim_prevstate;    // 直前のアニメ状態
    AnimationState anim_currentstate; // 現在のアニメ状態

    // 利用可能なアニメーションの辞書（アニメID -> 状態）
    std::unordered_map<int, AnimationState> animation_data;
};