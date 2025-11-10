#pragma once

// 敵の位置移動ロジック
class EnemyMove
{
public:
	EnemyMove();
	~EnemyMove();

	VECTOR MoveToOrigin(const VECTOR& enemypos);                    // 原点付近に戻る移動
	VECTOR MoveToSky(const VECTOR& enemypos);                       // 上空へ移動（退避）
	VECTOR MoveToTarget(const VECTOR& enemypos, const VECTOR& targetpos); // ターゲットへ接近移動

	const bool& GetIsOrigin() const { return move_is_origin; } // 原点にいるか

private:
	static constexpr float MOVE_SPEED = 0.125f;   // 基本移動速度
	static constexpr float ORIGIN_OFFSET = 0.1f;  // 原点とみなす誤差
	static constexpr float TARGETSKY_HIGHT = 10.0f; // 退避高さ
	bool move_is_origin; // 現在原点にいるか
};