#pragma once

// 行動木（将来のAI用ベース）
class BehaviorTree
{
public:
	BehaviorTree();
	~BehaviorTree();

	enum class Status
	{
		Idle,
		Success,
		Failure,
		Running,
	};

private:
};

