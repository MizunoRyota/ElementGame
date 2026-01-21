#include "stdafx.hpp"
#include "Collision.hpp"


Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::CheckSphereCapsuleCollision(const VECTOR& sphere_center, float sphereRadius, const VECTOR& capsule_base, float capsule_radius, float capsule_height)
{

    // カプセル軸上の最近点を求める

    VECTOR capsuleHeight = VAdd(capsule_base, VGet(0, capsule_height,0));

    VECTOR dot = VSub(capsuleHeight, capsule_base);
    VECTOR m = VSub(sphere_center, capsule_base);

    float projection = VDot(m, dot) / VDot(dot, dot);
    projection = std::clamp(projection, 0.0f, 1.0f);
    
    VECTOR closest = VAdd(capsule_base, VScale(dot, projection));

    // 球中心と最近点の距離
    float distance = VSize(VSub(sphere_center, closest));

    // 距離が合計半径以下なら衝突
    return distance <= (sphereRadius + capsule_radius);

}

bool Collision::CheckCapsuleCapsuleCollision(const VECTOR& capsule1Base, float capsule1Radius, float capsule1Height,
	const VECTOR& capsule2Base, float capsule2Radius, float capsule2Height)
{
	const VECTOR capsule1Top = VAdd(capsule1Base, VGet(0, capsule1Height, 0));
	const VECTOR capsule2Top = VAdd(capsule2Base, VGet(0, capsule2Height, 0));

	float minDistance = Segment_Segment_MinLength(capsule1Base, capsule1Top, capsule2Base, capsule2Top);
	const float collideRange = capsule1Radius + capsule2Radius;

	return minDistance <= collideRange;
}

float Collision::GetCapsuleCapsuleMinDistance(const VECTOR& capsule1Base, float capsule1Radius, float capsule1Height,
    const VECTOR& capsule2Base, float capsule2Radius, float capsule2Height)
{
    const VECTOR capsule1Top = VAdd(capsule1Base, VGet(0, capsule1Height, 0));
    const VECTOR capsule2Top = VAdd(capsule2Base, VGet(0, capsule2Height, 0));

    const float minDistance = Segment_Segment_MinLength(capsule1Base, capsule1Top, capsule2Base, capsule2Top);
    const float overlap = (capsule1Radius + capsule2Radius) - minDistance;

    return overlap;
}


bool Collision::CheckSegmentSegmentColliison(const VECTOR& charaOriginPosition, const VECTOR& charaEndPosition, const VECTOR& LaserOriginPosition, const VECTOR& LaserEndPosition)
{
   float length = Segment_Segment_MinLength(charaOriginPosition, charaEndPosition, LaserOriginPosition, LaserEndPosition);

    // 距離が合計半径以下なら衝突
    return length <= SEGMENT_COLLISION_MAX;
}