#pragma once

class ShotManager
{
public:
	ShotManager();
	~ShotManager();
	VECTOR Update();

	const VECTOR& GetPosition() const { return position; }

private:
	VECTOR position;
};

ShotManager::ShotManager()
{
}

ShotManager::~ShotManager()
{
}