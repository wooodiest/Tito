#pragma once
/// External Dependencies
#include <cmath>
#include <iostream>
//////////////////////////////////////////////////////////////////////////
class Vec2
{
public: 
	float x, y;

public: 
	Vec2() : x(0.0f), y(0.0f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}

public: 
	float Vec2_M() const
	{
		return std::sqrt(x * x + y * y);
	}
	int versorX()
	{
		return (x >= 0) ? 1 : -1;
	}
	int versorY()
	{
		return (y >= 0) ? 1 : -1;
	}

public: 
	Vec2 operator+ (const Vec2& v)
	{
		return { x + v.x, y + v.y };
	}
	Vec2 operator- (const Vec2& v)
	{
		return { x - v.x, y - v.y };
	}
	Vec2 operator* (const float& n)
	{
		return { x * n, y * n };
	}
	Vec2 operator/ (const float& n)
	{
		return { x / n, y / n };
	}
	Vec2& operator+=(const Vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2& operator-=(const Vec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2& operator*=(const float& n)
	{
		x *= n;
		y *= n;
		return *this;
	}

	Vec2& operator/=(const float& n)
	{
		x /= n;
		y /= n;
		return *this;
	}
};
