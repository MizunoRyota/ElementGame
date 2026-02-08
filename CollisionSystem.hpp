#pragma once

class GameObject;
class SharedData;
class Bullet;

class CollisionSystem
{
public:
	// すべての移動更新が終わった後に呼び出す
	static void Resolve(SharedData& shared);

private:
	static constexpr int JOYPAD_VIBERATON_POWER = 2000; // パッドの振動の強さ
	static constexpr int JOYPAD_VIBERATON_TIME = 200; // パッドの振動する時間

	float bullet_collision_radius = 3.0f;

	std::shared_ptr<SharedData> shred_data;

};