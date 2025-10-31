#pragma once
#include "GameObject.hpp"

// 影（シャドウマップ関連）
class Shadow : public GameObject
{
public:
	Shadow();
	~Shadow();

	void Initialize() override; // 初期化
	void Update() override;     // 更新
	void Draw() override ;      // 描画

	// シーン別描画（基本不要）
	void DrawTitle() override {};
	void DrawGameOver() override {};
	void DrawGameClear() override {};

	// シーン別更新（なし）
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};

	int GetShadowMapHandle() const { return obj_modelhandle; }  // 影のハンドル
	VECTOR GetLightDir()const { return obj_direction; }         // ライト方向

private:
	static constexpr int SHADOW_QUALITY = 2048;        // 影解像度
	static constexpr float SHADOW_ANGLESPEED = 0.001f; // 回転速度
};