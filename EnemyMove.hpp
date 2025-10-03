#pragma once

class EnemyMove
{
public:

	EnemyMove();
	~EnemyMove();

	VECTOR MoveToOrigin(const VECTOR& enemypos);        // 原点へ徐々に戻る移動
	VECTOR MoveToSky(const VECTOR& enemypos);           // 上空へ移動(浮上)
	VECTOR MoveToTarget(const VECTOR& enemypos, const VECTOR& targetpos); // ターゲットへ追従移動

	const bool& GetIsOrigin() const { return move_isorigin; } // 原点滞在状態

private:
	static constexpr float MOVE_SPEED = 0.125f;   // 共通移動速度
	static constexpr float ORIGIN_OFFSET = 0.1f;  // 原点とみなす許容距離
	static constexpr float TARGETSKY_HIGHT = 10.0f; // 浮上目標高さ
	bool move_isorigin; // 現在原点にいるか
};