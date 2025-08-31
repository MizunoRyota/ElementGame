#pragma once
#include <memory>

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Initialize(const VECTOR& pos, const VECTOR& dir, const float& speed);

	void Update();

	void Draw();

	void ChangeActiveTrue();

	void ChangeActiveFalse();

	bool IsActive() const { return bullet_isactive; }

private:
	
	static constexpr float BULLET_LIFE = 30;

	bool bullet_isactive;
	float bullet_speed;

	VECTOR bullet_position;
	VECTOR bullet_prevposition;
	VECTOR bullet_direction;

	std::shared_ptr<Bullet> bullet_next;

};
