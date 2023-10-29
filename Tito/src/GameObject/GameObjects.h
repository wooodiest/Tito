#pragma once

#include <vector>
#include "../Core/Engine.h"
#include "../Math/Vec2.h"
#include <SDL.h>
#include <SDL_image.h>
#include "../Physics/RigidBody.h"

enum class Color
{
	Blue = 1,
	Green,
	Grey,
	Orange,
	Pink,
	Purple,
	Yellow
};

class GameObjects
{
public: /// singleton instance
	static GameObjects& GetInstance()
	{
		static GameObjects instance;
		return instance;
	}
public:
	void Update(float deltaTime)
	{
		for (auto& rigitBody : data)
			rigitBody->Update(deltaTime);
	}
	void Render()
	{
		for (auto& rigitBody : data)
			rigitBody->Render();
	}

	void Add(const char* name, Color color, float mass, float radius,
		Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance = TAKE_AIR_RESSISTANCE);

	void Add(const char* name, float mass, float radius,
		Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance = TAKE_AIR_RESSISTANCE);

	void Add(Color color, float mass, float radius,
		Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance = TAKE_AIR_RESSISTANCE);

	void Add(float mass, float radius, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance = TAKE_AIR_RESSISTANCE);

private:
	SDL_Texture* GetTexture(int color);

private:
	SDL_Rect srcRect;
	std::vector<RigidBody*> data;

private: /// singleton - hiding or deleting all initializations
	GameObjects()
		: srcRect({ 0, 0, 50 ,50 }){}
	GameObjects(const GameObjects&) = delete;
	GameObjects& operator=(const GameObjects&) = delete;
	GameObjects(GameObjects&&) = delete;
	GameObjects& operator=(GameObjects&&) = delete;
	~GameObjects() {}
};

