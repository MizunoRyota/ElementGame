#pragma once
#include "CharacterBase.hpp" 

class CharacterBase;
class GameObject;

// クリスタル（敵の周囲を回るギミック）
class Crystal : public CharacterBase
{
public:

	Crystal();
	~Crystal();

	void LoadJson();

	void Initialize() override;   // 初期化（モデル/状態）

	void Update() override;       // 毎フレーム更新

	void UpdateStateAction() override {}; // 各派生で行動ステート更新

	void UpdateHandEffect() override {};

	void InitializeStates() override {};

	void DrawTitle() override {};
	void Draw() override;				// 描画
	void DrawGameOver() override {};
	void DrawGameClear() override {};

	// シーン別更新（必要ならオーバーライド）
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};
	void UpdateTutorial() override {};

	void ChangeActive();   // 有効/無効切替
	void ChangeBreak();    // 破壊切替
	void MoveHorizontal(); // 水平移動（周回）

    void ChangeCrystalIsBreak()		  { crystal_is_break = false; }		// 破壊状態リセット

	bool GetCrystalIsInit()		const { return crystal_is_active; }		// 破壊状態リセット

	bool GetCrystalIsBreak()	const { return crystal_is_break; } // 

private:

	static constexpr float CRYSTAL_SCALE = 0.010f;   // モデルの大きさ
	static constexpr float ROTATION_RADIUS = 7.0f;  // 周回半径
	static constexpr float ROTATION_SPEED = 0.015f;  // 角速度(rad/frame 相当)
	static constexpr int   CRYSTAL_MAXHP = 10;       // 最大HP
	static constexpr float OFFSET_Y = 7.0f;         // Y方向オフセット

	bool crystal_is_active;     // 初期化済みか
	bool crystal_is_break;    // 破壊状態か
	float crystal_angle;      // 現在の角度

	json crystal_json_data;

};
