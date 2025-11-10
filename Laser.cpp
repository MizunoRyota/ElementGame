#include "stdafx.hpp"
#include "Laser.hpp"

Laser::Laser()
{
	laser_ready = false;
}

Laser::~Laser()
{
}

void Laser::Initialize()
{
	laser_ready = false;
}

void Laser::PrepareLaser()
{
	laser_ready = true;
}

void Laser::FireLaser()
{
	laser_ready = false;
}