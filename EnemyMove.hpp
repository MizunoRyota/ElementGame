#pragma once

class EnemyMove
{
public:
	EnemyMove();
	~EnemyMove();

	VECTOR MoveToOrigin(const VECTOR& enemypos);

	VECTOR MoveToSky(const VECTOR& enemypos);

	VECTOR MoveToTarget(const VECTOR& enemypos, const VECTOR& targetpos);

	const bool& GetIsOrigin() const { return move_isorigin; }


private:
	static constexpr float MOVE_SPEED = 0.075f;	//アニメーションを進める速度
	static constexpr float ORIGIN_OFFSET = 0.1f;	//アニメーションを進める速度


	bool move_isorigin;
};