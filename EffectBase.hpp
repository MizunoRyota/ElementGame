#pragma once

class EffectBase
{
public:
	EffectBase();
	~EffectBase();
	void Update(const VECTOR& position);
	void PlayEffect();
	void SetPosition(const VECTOR& positon);
	void DrawEffect();
protected:
	static constexpr float EffectHight = 0.0f;	//再生しているエフェクトの高さ
	static constexpr float EffectScale = 4.5f;	//再生しているエフェクトの高さ
	static constexpr float PlayEffectSpeed = 0.20f;	//再生速度
	static constexpr float EndTime = 120.0f;	//再生速度

	int effectHandle;		// エフェクトリソースを読み込む。
	int StageEffect;		// ステージのエフェクト
	int playingEffectHandle;// 再生中のエフェクト
	float time;				// 時間を初期化する(定期的にエフェクトを再生するため)
	bool effect_isplay;			// エフェクトが再生中かどうかを示すフラグ
	bool effect_isend;				// エフェクトが終了したかどうかを示すフラグ
	VECTOR position;		// エフェクトの位置
};
