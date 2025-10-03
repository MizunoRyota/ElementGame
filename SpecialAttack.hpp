#pragma once

class SpecialAttack
{
public:
	SpecialAttack();
	~SpecialAttack();

	const bool& GetIsCharge() const { return specialattack_ischarge; }
	const bool& GetIsActive() const { return specialattack_isactive; }
	const bool& GetIsEnd() const { return specialattack_isend; }

private:

	static constexpr float SPECIALATTACK_CHARGE_TIME = 5.0f; // É`ÉÉÅ[ÉWéûä‘(ïb)
	bool specialattack_ischarge;
	bool specialattack_isactive;
	bool specialattack_isend;

};
