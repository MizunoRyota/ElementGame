#include "stdafx.hpp"
#include "CharacterBase.hpp"
#include "src/Sounds/SoundManager.hpp"
// ダメージ適用。無敵/既に死亡/0以下なら適用しない
bool CharacterBase::TakeDamage(int amount)
{
	if (amount <= 0) return false;
	if (IsDead()) return false;
	if (IsInvincible()) return true;

	SoundManager::GetSoundManager().PlayOnEnemySe();
	ChangeColor();
	obj_hp -= amount;

	if (obj_hp < 0) obj_hp = 0;
	damage_invincible_timer = damage_invincible_duration; // 無敵開始
	return true;
}

void CharacterBase::ChangeColor()
{
	MV1SetMaterialDifColor(obj_modelhandle, 0, Pallet::Red_F.GetHandleF());
}

// 無敵タイマーの進行（毎フレーム呼ぶ)
void CharacterBase::TickDamageCooldown()
{
	if (damage_invincible_timer > 0)
	{
		damage_invincible_timer--;
	}
	if (damage_invincible_timer<=0)
	{
		MV1SetMaterialDifColor(obj_modelhandle, 0, Pallet::White_F.GetHandleF());
	}
}

// 行動範囲外に出ないよう、中心(0,0,0)基準で押し戻す
void CharacterBase::CheckMoveRange()
{
	// 中心から距離
	float range = VSize(VSub(obj_position, VGet(0.0f, 0.0f, 0.0f)));

	// 一定の距離に達したら押し戻す
	if (range > MAX_RANGE || range < -MAX_RANGE)
	{
		// 中心->現在位置ベクトル（戻す向き)
		VECTOR distance = VSub(VGet(0.0f, 0.0f, 0.0f), obj_position);
		distance = VNorm(distance);

		// 戻す量を計算
		VECTOR returnPosition = VScale(distance, (range - MAX_RANGE));

		obj_position = VAdd(obj_position, returnPosition);
	}

}