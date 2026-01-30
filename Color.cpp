#include "stdafx.hpp"

#include"Color.hpp"

int Color::GetHandle()const
{
    return GetColor(R, G, B);
}

COLOR_F Color::GetHandleF()const
{
    return GetColorF(R_F, G_F, B_F, 1.0f);
}