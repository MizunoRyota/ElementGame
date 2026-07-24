#pragma once

class Collision
{
public:
	Collision();
	~Collision();

	// 球とカプセルの当たり判定
	static bool CheckSphereCapsuleCollision(const VECTOR& sphereCenter, float sphereRadius, const VECTOR& capsuleBase, float capsule_radius, float capsuleHeight);

	// 線分同士の当たり判定
	static bool CheckSegmentSegmentColliison(const VECTOR& charaPosition, const VECTOR& charaPositionHeight, const VECTOR& LaserPosition, const VECTOR& LaserEndPosition);

	// カプセル同士の当たり判定
	static bool CheckCapsuleCapsuleCollision(const VECTOR& capsule1Base, float capsule1Radius, float capsule1Height,
		const VECTOR& capsule2Base, float capsule2Radius, float capsule2Height);

	// カプセル同士の最短距離を取得
	static float GetCapsuleCapsuleMinDistance(const VECTOR& capsule1Base, float capsule1Radius, float capsule1Height,
		const VECTOR& capsule2Base, float capsule2Radius, float capsule2Height);

private:

	static constexpr float SEGMENT_COLLISION_MAX = 3.0f; // 線分判定の最大距離

	float segment_min_distance; // 線分最短距離の一時保持

};
