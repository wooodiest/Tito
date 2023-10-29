#include "Coordinates.h"
/// Set values of display coordinates (0, 0) which is bottom left corner with margin
int Coords::CoordsX0 = DISPLAY_MARGIN;
int Coords::CoordsY0 = WINDOW_HEIGHT - DISPLAY_MARGIN;

/// Calculates new coords depending on coordinates
int Coords::X(int x)
{
	return CoordsX0 + x;
}

int Coords::Y(int y)
{
	return CoordsY0 - y;
}

int Coords::X(float x)
{
	return CoordsX0 + static_cast<int>(x);
}

int Coords::Y(float y)
{
	return CoordsY0 - static_cast<int>(y);
}