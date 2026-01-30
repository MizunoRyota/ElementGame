#pragma once

class  Color
{
public:
	constexpr Color()
		: R{ 0 }
		, G{ 0 }
		, B{ 0 } 
		, R_F{ 0.0f }
		, G_F{ 0.0f }
		, B_F{ 0.0f }
	{
	}

	constexpr Color(float R, float G, float B)
		: R{ static_cast<int>(R) }
		, G{ static_cast<int>(G) }
		, B{ static_cast<int>(B) }
		, R_F{ R }
		, G_F{ G }
		, B_F{ B }
	{
	}

	int GetHandle() const;
	COLOR_F GetHandleF() const;

private:
	int R;
	int G;
	int B;
	float R_F;
	float G_F;
	float B_F;

};