#include "Dxlib.h"
#include "HitChecker.hpp"
#include "BulletManager.hpp"
#include <cmath>
HitChecker::HitChecker()
	:character_position(VGet(0, 0, 0))
	, object_position(VGet(0, 0, 0))
	, both_distance(VGet(0, 0, 0))
	, ishit(false)
	, totalradius(0.0f)
	, object_radius(0.5f)
	, character_radius(1.0f)
{
}

HitChecker::~HitChecker()
{}

bool HitChecker::Update(const VECTOR& objectpos, const VECTOR& playerPos)
{
    ishit = false;
    character_position = VAdd(playerPos, VGet(0, 1.5f, 0));
    both_distance = VSub(objectpos, character_position);
    totalradius = object_radius + character_radius;
    distance = VSquareSize(both_distance);

    if (distance <= (totalradius * totalradius))
    {
        ishit = true;
    }

    return ishit;
}