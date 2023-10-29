#pragma once
/// Internal Dependencies
#include "../Core/Engine.h"
#include "Color.h"
/// External Dependencies
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//////////////////////////////////////////////////////////////////////////
class TextureManager
{
public:
	static TextureManager& GetInstance() /// singleton instance
	{
		static TextureManager instance;
		return instance;
	}
public:
	SDL_Texture* LoadTexture(const char* source);
	SDL_Texture* Loadtext(const char* text, TTF_Font* font = Engine::GetInstance().GetFont(), SDL_Color color = COORDINATES_SYSTEM_AXES_COLOR_TEXT);
	void Draw(SDL_Texture* texture, SDL_Rect src, int x, int y);
	void DrawText(const char* text, int x, int y, TTF_Font* font = Engine::GetInstance().GetFont(), SDL_Color color = COORDINATES_SYSTEM_AXES_COLOR_TEXT);
	void DrawCircleWithScale(SDL_Texture* texture, SDL_Rect src, float x, float y, float r);

private: /// singleton - hiding or deleting all initializations
	TextureManager() {}
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator= (const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;
	~TextureManager() {}

};

