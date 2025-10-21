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
	 void Initialize() override {};
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

	void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { reference_enemy = setenemy; }

private:
	static constexpr float CRYSTAL_SCALE = 0.010f;			 //モデルの大きさ

	static constexpr int CRYSTAL_MAXHP = 20;				 // クリスタルの最大HP

	std::shared_ptr<Enemy> reference_enemy;		//敵の参照用

};
