#include "stdafx.hpp"
#include "Palsy.hpp"
#include "Enemy.hpp"

Palsy::Palsy()
{
	ispalsy = true;
	palsy_time = PALSY_TIME;
}

Palsy::~Palsy()
{
}

void Palsy::ChangeIsPalsy()
{
	ispalsy = false;
}

void Palsy::Update()
{
	palsy_time -= PALSY_DECREASE_TIME;

	if (palsy_time <= 0.0f)
	{
		ChangeIsPalsy();
	}

}