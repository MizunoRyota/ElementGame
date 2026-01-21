#pragma once
#include "stdafx.hpp"

class IState
{
public:
	IState() = default;;
	virtual ~IState() = default;

	virtual void Enter() abstract;		//Å‰‚ÉŒÄ‚Î‚ê‚éˆ—
	virtual void Update() abstract;		//XV
	virtual void Exit() abstract;		//”²‚¯o‚·‚ÉŒÄ‚Î‚ê‚éˆ—

private:

};