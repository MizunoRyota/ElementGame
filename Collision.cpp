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

    VECTOR d = VSub(capsuleHeight, capsule_base);
    VECTOR m = VSub(sphere_center, capsule_base);

    float projection = VDot(m, d) / VDot(d, d);
    projection = std::clamp(projection, 0.0f, 1.0f);
    
    VECTOR closest = VAdd(capsule_base, VScale(d, projection));

    // 球中心と最近点の距離
    float distance = VSize(VSub(sphere_center, closest));

    // 距離が合計半径以下なら衝突
    return distance <= (sphereRadius + capsule_radius);

}
