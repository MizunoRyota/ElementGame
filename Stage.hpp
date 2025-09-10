#pragma once

#include "GameObject.hpp"
class Effect;
class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Initialize()override;		//‰Šú‰»
	void Update()override;			//XV
	void Draw()override;			//•`‰æ

private:
	// Ã“I’è”.
	static constexpr float SCALE = 0.0125f;		//‘å‚«‚³
	static constexpr float STAGE_HIGHT = 1.0f;		//‘å‚«‚³

};