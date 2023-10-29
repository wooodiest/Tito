#include "GameObjects.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../Graphics/TextureManager.h"

void GameObjects::Add(const char* name, Color color, float mass, float radius, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance /*= TAKE_AIR_RESSISTANCE*/)
{
	data.emplace_back(new RigidBody(name, GetTexture(static_cast<int>(color)), srcRect, mass, radius, position, velocity, acceleration, force, airResistance));
}

void GameObjects::Add(const char* name, float mass, float radius, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance /*= TAKE_AIR_RESSISTANCE*/)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int color = (std::rand() % 7) + 1;
	data.emplace_back(new RigidBody(name, GetTexture(color), srcRect, mass, radius, position, velocity, acceleration, force, airResistance));
}

void GameObjects::Add(Color color, float mass, float radius, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance /*= TAKE_AIR_RESSISTANCE*/)
{
	const char* name = "ball";
	data.emplace_back(new RigidBody(name, GetTexture(static_cast<int>(color)), srcRect, mass, radius, position, velocity, acceleration, force, airResistance));
}

void GameObjects::Add(float mass, float radius, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance /*= TAKE_AIR_RESSISTANCE*/)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int color = (std::rand() % 7) + 1;
	const char* name = "ball";
	data.emplace_back(new RigidBody(name, GetTexture(static_cast<int>(color)), srcRect, mass, radius, position, velocity, acceleration, force, airResistance));
}

SDL_Texture* GameObjects::GetTexture(int color)
{
	switch (color)
	{
	case 1:
		return TextureManager::GetInstance().LoadTexture("assets/ball_blue.png");
		break;
	case 2:
		return TextureManager::GetInstance().LoadTexture("assets/ball_green.png");
		break;
	case 3:
		return TextureManager::GetInstance().LoadTexture("assets/ball_grey.png");
		break;
	case 4:
		return TextureManager::GetInstance().LoadTexture("assets/ball_orange.png");
		break;
	case 5:
		return TextureManager::GetInstance().LoadTexture("assets/ball_pink.png");
		break;
	case 6:
		return TextureManager::GetInstance().LoadTexture("assets/ball_purple.png");
		break;
	case 7:
		return TextureManager::GetInstance().LoadTexture("assets/ball_yellow.png");
		break;
	default:
		return TextureManager::GetInstance().LoadTexture("assets/ball_blue.png");
		break;
	}
}
