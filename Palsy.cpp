#include "stdafx.hpp"
#include "Palsy.hpp"
#include "Enemy.hpp"

Palsy::Palsy()
{
	is_palsy = true;
	palsy_time = PALSY_TIME;
}

Palsy::~Palsy()
{
}

void Palsy::ChangeIsPalsy()
{
	is_palsy = false;
}

void Palsy::Update()
{
	palsy_time -= PALSY_DECREASE_TIME;

	if (palsy_time <= 0.0f)
	{
		ChangeIsPalsy();
	}

}