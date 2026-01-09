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


bool Collision::CheckSegmentSegmentColliison(const VECTOR& charaOriginPosition, const VECTOR& charaEndPosition, const VECTOR& LaserOriginPosition, const VECTOR& LaserEndPosition)
{
   float length = Segment_Segment_MinLength(charaOriginPosition, charaEndPosition, LaserOriginPosition, LaserEndPosition);

    // 距離が合計半径以下なら衝突
    return length <= SEGMENT_COLLISION_MAX;
}