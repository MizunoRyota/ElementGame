#pragma once
#include "GameObject.hpp"
class Effect : public GameObject
{
public:
	Effect(int effect_handle);
	~Effect();

	void Update(const VECTOR& position);
	void UpdateEffect();
	void PlayEffect();
	void SetPosition(const VECTOR& position);
	void DrawEffect();

private:
	static constexpr float EFFECT_HIGHT = 0.3f;	//再生しているエフェクトの高さ
	static constexpr float EFFECT_SCALE = 4.5f;	//再生しているエフェクトの高さ
	static constexpr float EFFCT_PLAYSPEED = 0.20f;	//再生速度
	static constexpr float EFFECT_ENDTIME = 120.0f;	//再生速度

	int effect_handle;			// エフェクトリソースを読み込む。
	int effect_playinghandle;	// 再生中のエフェクト
	float effect_playtime;		// 時間を初期化する(定期的にエフェクトを再生するため)
	bool effect_isplay;			// エフェクトが再生中かどうかを示すフラグ
	bool effect_isend;			// エフェクトが終了したかどうかを示すフラグ
	VECTOR effect_position;		// エフェクトの位置
};
