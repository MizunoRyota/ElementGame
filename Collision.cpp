#include "stdafx.hpp"
#include "Collision.hpp"

Collision::Collision()
{
}

Collision::~Collision()
{
}

/// <summary>
/// 球とカプセルの衝突判定
/// </summary>
/// <param name="sphere_center">球の中心座標。</param>
/// <param name="sphereRadius">球の半径。</param>
/// <param name="capsule_base">カプセルの基点座標。</param>
/// <param name="capsule_radius">カプセルの半径。</param>
/// <param name="capsule_height">カプセルの高さ。</param>
/// <returns>球とカプセルが衝突している場合はtrue、それ以外はfalse。</returns>
bool Collision::CheckSphereCapsuleCollision(const VECTOR& sphere_center, float sphereRadius, const VECTOR& capsule_base, float capsule_radius, float capsule_height)
{

    // カプセル軸上の最近点を求める

    VECTOR capsuleHeight = VAdd(capsule_base, VGet(0, capsule_height,0));

    capsuleHeight = VSub(capsuleHeight, capsule_base);
    VECTOR distance = VSub(sphere_center, capsule_base);

    float projection = VDot(distance, capsuleHeight) / VDot(capsuleHeight, capsuleHeight);
    projection = std::clamp(projection, 0.0f, 1.0f);
    
    VECTOR closest = VAdd(capsule_base, VScale(capsuleHeight, projection));

    // 球中心と最近点の距離
    float length = VSize(VSub(sphere_center, closest));

    // 距離が合計半径以下なら衝突
    return length <= (sphereRadius + capsule_radius);

}

/// <summary>
/// 2つのカプセル間の衝突判定
/// </summary>
/// <param name="capsule1Base">1つ目のカプセルの底面中心座標。</param>
/// <param name="capsule1Radius">1つ目のカプセルの半径。</param>
/// <param name="capsule1Height">1つ目のカプセルの高さ。</param>
/// <param name="capsule2Base">2つ目のカプセルの底面中心座標。</param>
/// <param name="capsule2Radius">2つ目のカプセルの半径。</param>
/// <param name="capsule2Height">2つ目のカプセルの高さ。</param>
/// <returns>2つのカプセルが衝突している場合はtrue、それ以外はfalse。</returns>
bool Collision::CheckCapsuleCapsuleCollision(const VECTOR& capsule1Base, float capsule1Radius, float capsule1Height,
	const VECTOR& capsule2Base, float capsule2Radius, float capsule2Height)
{
	// 各カプセルの上端を求める
	const VECTOR capsule1Top = VAdd(capsule1Base, VGet(0, capsule1Height, 0));
	const VECTOR capsule2Top = VAdd(capsule2Base, VGet(0, capsule2Height, 0));

	// 線分同士の最短距離で判定
	float minDistance = Segment_Segment_MinLength(capsule1Base, capsule1Top, capsule2Base, capsule2Top);
	const float collideRange = capsule1Radius + capsule2Radius;

	return minDistance <= collideRange;
}

/// <summary>
/// 2つのカプセル間の最小距離
/// </summary>
/// <param name="capsule1Base">最初のカプセルの底面の中心座標。</param>
/// <param name="capsule1Radius">最初のカプセルの半径。</param>
/// <param name="capsule1Height">最初のカプセルの高さ。</param>
/// <param name="capsule2Base">2番目のカプセルの底面の中心座標。</param>
/// <param name="capsule2Radius">2番目のカプセルの半径。</param>
/// <param name="capsule2Height">2番目のカプセルの高さ。</param>
/// <returns>2つのカプセル間の重なり量。正の値は重なりを示し、負の値は距離を示します。</returns>
float Collision::GetCapsuleCapsuleMinDistance(const VECTOR& capsule1Base, float capsule1Radius, float capsule1Height,
    const VECTOR& capsule2Base, float capsule2Radius, float capsule2Height)
{
    // 各カプセルの上端を求める
    const VECTOR capsule1Top = VAdd(capsule1Base, VGet(0, capsule1Height, 0));
    const VECTOR capsule2Top = VAdd(capsule2Base, VGet(0, capsule2Height, 0));

    // カプセル同士の重なり量（正なら重なり）
    const float minDistance = Segment_Segment_MinLength(capsule1Base, capsule1Top, capsule2Base, capsule2Top);
    const float overlap = (capsule1Radius + capsule2Radius) - minDistance;

    return overlap;
}

/// <summary>
/// 2つの線分間の衝突判定
/// </summary>
/// <param name="charaOriginPosition">キャラクターの線分の始点位置。</param>
/// <param name="charaEndPosition">キャラクターの線分の終点位置。</param>
/// <param name="LaserOriginPosition">レーザーの線分の始点位置。</param>
/// <param name="LaserEndPosition">レーザーの線分の終点位置。</param>
/// <returns>2つの線分間の最短距離が衝突判定閾値以下の場合はtrue、それ以外の場合はfalse。</returns>
bool Collision::CheckSegmentSegmentColliison(const VECTOR& charaOriginPosition, const VECTOR& charaEndPosition, const VECTOR& LaserOriginPosition, const VECTOR& LaserEndPosition)
{
   // 線分同士の最短距離で判定
   float length = Segment_Segment_MinLength(charaOriginPosition, charaEndPosition, LaserOriginPosition, LaserEndPosition);

    // 距離が合計半径以下なら衝突
    return length <= SEGMENT_COLLISION_MAX;
}