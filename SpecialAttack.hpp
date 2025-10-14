#pragma once

class SpecialAttack
{
public:
	SpecialAttack();
	~SpecialAttack();

	void Initialize();

	void UpdateChrgeCount();

	void ChangeIsChargeFlag();

	const bool& GetIsCharge() const { return specialattack_ischarge; }
	const bool& GetIsActive() const { return specialattack_isactive; }
	const bool& GetIsEnd() const { return specialattack_isend; }

private:

	static constexpr float SPECIALATTACK_CHARGE_TIME = 5000.0f; // チャージ時間(秒)
	static constexpr float SPECIALATTACK_CHARGE_DECREACENUM = 5.0f; // チャージ速度

	float specialattack_charge_time;

	bool specialattack_ischarge;
	bool specialattack_isactive;
	bool specialattack_isend;

};
