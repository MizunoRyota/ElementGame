#pragma once
#include "CharacterBase.hpp" 

class CharacterBase;
class GameObject;
class Enemy;

// クリスタル（敵の周囲を回るギミック）
class Crystal : public CharacterBase
{
public:

	Crystal();
	~Crystal();
	void Initialize() override;   // 初期化（モデル/状態）
	void Update() override;       // 毎フレーム更新

	void UpdateStateAction() override {};

	void DrawTitle() override {};
	void Draw() override;         // 描画
	void DrawGameOver() override {};
	void DrawGameClear() override {};

	// シーン別更新（必要ならオーバーライド）
	void UpdateGameClear() override {};
	void UpdateGameOver() override {};
	void UpdateTitle() override {};

	void ChangeActive();   // 有効/無効切替
	void ChangeBreak();    // 破壊切替
	void MoveHorizontal(); // 水平移動（周回）

	void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { enemy_reference = setenemy; }

private:
	static constexpr float CRYSTAL_SCALE = 0.010f;   // モデルの大きさ
	static constexpr float ROTATION_RADIUS = 10.0f;   // 周回半径
	static constexpr float ROTATION_SPEED = 0.015f;  // 角速度(rad/frame 相当)
	static constexpr int   CRYSTAL_MAXHP = 20;       // 最大HP
	static constexpr float offset_y = 10.0f;         // Y方向オフセット

	bool crystal_init;     // 初期化済みか
	bool crystal_break;      // 破壊状態か
	float crystal_angle;     // 現在の角度

	std::shared_ptr<Enemy> enemy_reference; // 敵参照（軌道中心など）

};
