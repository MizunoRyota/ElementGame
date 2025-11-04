#pragma once

class Laser
{
public:
	Laser();
	~Laser();

	void PrepareLaser();//レーザーを発射可能状態にする

	void FireLaser();

	bool GetLaserReady() const { return laser_ready; } // 衝突半径

private:
	static constexpr float LASER_ = 20;  // 発射クール時間

	bool laser_ready;

};
