#pragma once

#include "GameObject.hpp" 
class GameObject;

class Crystal : public GameObject
{
public:

	Crystal();
	~Crystal();
	 void Initialize() override {};
	 void Update() override {};

	 void DrawTitle() override {};
	 void Draw() override {};
	 void DrawGameOver() override {};
	 void DrawGameClear() override {};

	// 追加: シーン別更新処理（必要なクラスでオーバーライド）
	 void UpdateGameClear() override {};
	 void UpdateGameOver() override {};
	 void UpdateTitle() override {};

private:

};
