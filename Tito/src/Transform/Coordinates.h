#pragma once
/// Internal Dependencies
#include "../Core/Engine.h"
//////////////////////////////////////////////////////////////////////////

class Coords
{
public:
	static int CoordsX0;
	static int CoordsY0;
public:
	static int X(int x);
	static int Y(int y);

	static int X(float x);
	static int Y(float y);

};
