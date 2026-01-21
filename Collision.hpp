#pragma once

class Collision
{
public:
	Collision();
	~Collision();

	// ‹…‚ÆƒJƒvƒZƒ‹‚Ì“–‚½‚è”»’è
	static bool CheckSphereCapsuleCollision(const VECTOR& sphereCenter, float sphereRadius, const VECTOR& capsuleBase, float capsule_radius, float capsuleHeight);

	static bool CheckSegmentSegmentColliison(const VECTOR& charaPosition, const VECTOR& charaPositionHeight, const VECTOR& LaserPosition, const VECTOR& LaserEndPosition);

	static bool CheckCapsuleCapsuleCollision(const VECTOR& capsule1Base, float capsule1Radius, float capsule1Height,
		const VECTOR& capsule2Base, float capsule2Radius, float capsule2Height);

	static float GetCapsuleCapsuleMinDistance(const VECTOR& capsule1Base, float capsule1Radius, float capsule1Height,
		const VECTOR& capsule2Base, float capsule2Radius, float capsule2Height);

private:

	static constexpr float SEGMENT_COLLISION_MAX = 3.0f;

	float segment_min_distance;

};
