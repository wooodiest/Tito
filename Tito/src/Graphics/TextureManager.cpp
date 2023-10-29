#include "TextureManager.h"
#include "../Transform/Camera.h"

SDL_Texture* TextureManager::LoadTexture(const char* source)
{
	SDL_Surface* tempSurface = IMG_Load(source);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance().GetRenderer(), tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}

SDL_Texture* TextureManager::Loadtext(const char* text, TTF_Font* font, SDL_Color color )
{
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance().GetRenderer(), tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, int x, int y)
{
	SDL_Rect dest = { x, y, src.w, src.h };
	SDL_RenderCopy(Engine::GetInstance().GetRenderer(), texture, &src, &dest);
}

void TextureManager::DrawText(const char* text, int x, int y, TTF_Font* font , SDL_Color color)
{
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance().GetRenderer(), tempSurface);
	SDL_Rect textRect = { x, y, tempSurface->w, tempSurface->h };
	SDL_RenderCopy(Engine::GetInstance().GetRenderer(), texture, nullptr, &textRect);
	SDL_FreeSurface(tempSurface);
	SDL_DestroyTexture(texture);
}

void TextureManager::DrawCircleWithScale(SDL_Texture* texture, SDL_Rect src, float x, float y, float r)
{
	/// Calculate width and height of sprite based on circle radius and current display scale
	int destWH = static_cast<int>(2 * r * DISPLAY_METER * DISPLAY_SCALE);
	int _x, _y;

	/// Calculate left corner of sprite
	if (destWH < MIN_SIZE_OF_TEXTURE) // if calculated dimensions are less than minimum to draw
	{
		destWH = MIN_SIZE_OF_TEXTURE;
		/// calculate dimensions besed on destWH -> r = destWH / (2 * r * DISPLAY_METER * DISPLAY_SCALE)
		_x = static_cast<int>(x * DISPLAY_METER * DISPLAY_SCALE - destWH / 2);
		_y = static_cast<int>(y * DISPLAY_METER * DISPLAY_SCALE + destWH / 2);
	}
	else
	{
		_x = static_cast<int>((x - r) * DISPLAY_METER * DISPLAY_SCALE);
		_y = static_cast<int>((y + r) * DISPLAY_METER * DISPLAY_SCALE);
	}
	if (_y - Camera::y() < 0 || _x - Camera::x() + destWH < 0)
		return;
	SDL_Rect destRect = {
		Coords::X(_x - Camera::x()),
		Coords::Y(_y - Camera::y()),
		destWH,
		destWH
	};
	SDL_RenderCopy(Engine::GetInstance().GetRenderer(), texture, &src, &destRect);
}
