#pragma once

class SharedData;

class CollisionSystem
{
public:
	// すべての移動更新が終わった後に呼び出す
	static void Resolve(SharedData& shared);
};