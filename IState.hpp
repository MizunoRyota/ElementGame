#pragma once
#include "stdafx.hpp"

class IState
{
public:
	IState() = default;;
	virtual ~IState() = default;;

	//virtual void Initialize() abstract;

	virtual void Enter() abstract;
	virtual void Update() abstract;
	virtual void Exit() abstract;

private:

};