#pragma once
#include "CharacterBase.hpp" 

class CharacterBase;
class GameObject;
class Enemy;

class Crystal : public CharacterBase
{
public:

	Crystal();
	~Crystal();
	 void Initialize() override;
	 void Update() override ;

	 void UpdateStateAction() override {};

	 void DrawTitle() override {};
	 void Draw() override ;
	 void DrawGameOver() override {};
	 void DrawGameClear() override {};

	// 追加: シーン別更新処理（必要なクラスでオーバーライド）
	 void UpdateGameClear() override {};
	 void UpdateGameOver() override {};
	 void UpdateTitle() override {};

	 void ChangeActive();
	 void ChangeBreak();
	 void MoveHorizontal();

	void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { reference_enemy = setenemy; }

private:
	static constexpr float CRYSTAL_SCALE = 0.010f;			 //モデルの大きさ
	static constexpr float ROTATION_RADIUS = 6.0f;    // 円の半径（必要に応じて調整）
	static constexpr float ROTATION_SPEED = 0.025f; // 角速度（ラジアン/frame）
	static constexpr int CRYSTAL_MAXHP = 20;				 // クリスタルの最大HP
	static constexpr float offset_y = 10.0f;	// Y軸は敵の位置に対して上にオフセットする

	bool crystal_isinit;
	bool crystal_break;
	float crystal_angle;

	std::shared_ptr<Enemy> reference_enemy;		//敵の参照用

};
