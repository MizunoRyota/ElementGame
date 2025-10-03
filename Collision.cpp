#include "stdafx.hpp"
#include "Collision.hpp"


Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::CheckSphereCapsuleCollision(const VECTOR& sphereCenter, float sphere_radius, const VECTOR& capsuleBase, float capsule_radius, float capsuleHeight)
{

    // カプセル軸上の最近点を求める

    VECTOR capsule_hight = VAdd(capsuleBase, VGet(0, capsuleHeight,0));

    VECTOR d = VSub(capsule_hight, capsuleBase);
    VECTOR m = VSub(sphereCenter, capsuleBase);

    float t = VDot(m, d) / VDot(d, d);
    t = std::clamp(t, 0.0f, 1.0f);
    
    VECTOR closest = VAdd(capsuleBase, VScale(d, t));

    // 球中心と最近点の距離
    float dist = VSize(VSub(sphereCenter, closest));

    // 距離が合計半径以下なら衝突
    return dist <= (sphere_radius + capsule_radius);

}
