#pragma once
#include "GameObject.hpp" 

class GameObject;
class Enemy;

class Crystal : public GameObject
{
public:

	Crystal();
	~Crystal();
	 void Initialize() override {};
	 void Update() override ;

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
	static constexpr float CRYSTAL_SCALE = 0.010f;

	std::shared_ptr<Enemy> reference_enemy;

};
