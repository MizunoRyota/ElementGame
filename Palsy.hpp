#pragma once
class Palsy
{
public:
	Palsy();
	~Palsy();

	void Update();

	void ChangeIsPalsy();

	const bool& GetIsPalsy() const { return ispalsy; }

private:
	static constexpr float PALSY_TIME = 3000.0f;               // 発射位置オフセット(Y方向・モデル調整)
	static constexpr float PALSY_DECREASE_TIME =10.0f;               // 発射位置オフセット(Y方向・モデル調整)

	bool ispalsy;
	float palsy_time;
};
