#pragma once
#include "IState.hpp"
#include "PlayerStateKind.hpp"
#include "ObjectAccessor.hpp"

class IState;

class PlayerStateBase : public IState
{
public:
	PlayerStateBase() = default;
	virtual ~PlayerStateBase() = default;
	// 次のステートの条件判別
	virtual PlayerStateKind GetNextState()abstract;

private:

};