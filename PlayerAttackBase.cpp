#include "Dxlib.h"
#include "EffekseerForDXLib.h"
#include "Camera.hpp"
#include "Input.hpp"
#include "PlayerBase.hpp"

PlayerAttackBase::PlayerAttackBase(int model_handle)
	:AngleVec(VGet(0, 0, 0))
	, position(VGet(0, 0, 0))
	, effect_handle(0)
	, time(0)
	, effect_isplay(true)
	, effect_isend(false)
	, flame_name(0)
	, model_handle(0)
{
	this->model_handle = model_handle;
	flame_name = MV1SearchFrame(model_handle,"f_middle.03.R");
}

PlayerAttackBase::~PlayerAttackBase()
{
}

void PlayerAttackBase::Update(const Input& input, const Camera& camera)
{
	
	//ˆ—‚È‚µ
}

void PlayerAttackBase::PlayEffect()
{
	//ˆ—‚È‚µ
}


void PlayerAttackBase::UpdateBullet(const Input& input, const Camera& camera)
{
	//ˆ—‚È‚µ
}