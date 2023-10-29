#pragma once
#include "SDL_stdinc.h"

struct ColorRGBA
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;

	ColorRGBA(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a):
		r(_r), g(_g), b(_b), a(_a) {}
};