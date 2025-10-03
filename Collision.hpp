#pragma once

class Collision
{
public:
	Collision();
	~Collision();

	// ‹…‚ÆƒJƒvƒZƒ‹‚Ì“–‚½‚è”»’è
	static bool CheckSphereCapsuleCollision(const VECTOR& sphereCenter,float sphere_radius,const VECTOR& capsuleBase,float capsule_radius,float capsuleHeight);

private:

	static constexpr float CAPCULE_HIGHT = 1.0f;

};
