#pragma once

class Collision
{
public:
	Collision();
	~Collision();

	// ‹…‚ÆƒJƒvƒZƒ‹‚Ì“–‚½‚è”»’è
	static bool CheckSphereCapsuleCollision(const VECTOR& sphereCenter,float sphereRadius,const VECTOR& capsuleBase,float capsule_radius,float capsuleHeight);

	static bool CheckSegmentSegmentColliison(const VECTOR& charaPosition, const VECTOR& charaPositionHeight, const VECTOR& LaserPosition, const VECTOR& LaserEndPosition);

private:

	static constexpr float SEGMENT_COLLISION_MAX = 3.0f;

};
