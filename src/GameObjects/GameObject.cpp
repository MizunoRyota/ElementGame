#include "../stdafx.hpp"
#include "../GameObject.hpp"
#include "../ObjectAccessor.hpp"

bool GameObject::ChengeDebugFlag()
{
	if ((CheckHitKey(KEY_INPUT_E) != 0) || ObjectAccessor::GetObjectAccessor().GetIsInputLeftShoulder() && ObjectAccessor::GetObjectAccessor().GetIsInputBottunA())
	{
		if (!obj_debug)
		{
			obj_debug = true;
			return obj_debug;
		}
	}
	if ((CheckHitKey(KEY_INPUT_Q) != 0) || ObjectAccessor::GetObjectAccessor().GetIsInputLeftShoulder() && ObjectAccessor::GetObjectAccessor().GetIsInputBottunB())
	{
		if (obj_debug)
		{
			obj_debug = false;
			return obj_debug;
		}
	}
	return obj_debug;

}
