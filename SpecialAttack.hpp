#pragma once

class SpecialAttack
{
public:
	SpecialAttack();
	~SpecialAttack();

	void Initialize();

	void UpdateChrgeCount();

	void ChangeIsChargeFlag();

	const bool& GetIsCharge() const { return specialattack_is_charge; }
	const bool& GetIsActive() const { return specialattack_is_active; }
	const bool& GetIsEnd() const { return specialattack_is_end; }

private:

	static constexpr float SPECIALATTACK_CHARGE_TIME = 3000.0f; // チャージ時間(秒)
	static constexpr float SPECIALATTACK_CHARGE_DECREACENUM = 7.50f; // チャージ速度

	float specialattack_charge_time;

	bool specialattack_is_charge;
	bool specialattack_is_active;
	bool specialattack_is_end;

};
