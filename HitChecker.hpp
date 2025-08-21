#pragma once

class BulletManager;

class HitChecker
{
public:
	HitChecker();
	~HitChecker();
	bool Update(const VECTOR& objectpos, const VECTOR& characterpos);
private:
	VECTOR object_position;
	VECTOR character_position;
	VECTOR both_distance;
	float object_radius;
	float character_radius;
	float totalradius;
	float distance;
	bool ishit;
};

