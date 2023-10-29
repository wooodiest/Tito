#pragma once

#include "../Math/Vec2.h"
#include "../Core/Engine.h"
#include "../Graphics/TextureManager.h"
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

class RigidBody
{
public:
	void Update(float deltaTime);
	void Render();
	void ApplyForce(Vec2 force);
	void DisplayParameters();
public:
	const char* name;
	SDL_Texture* texture;
	SDL_Rect srcRect;
private:
	float m_Mass;
	float m_Radius;
	float m_CrossSectionalArea;
	Vec2 m_Position;
	Vec2 m_Velocity;
	Vec2 m_Acceleration;
	Vec2 m_Force;
	bool m_IsOnGround;
	bool m_TakeAirResistance;

public:
	RigidBody(const char* _name, SDL_Texture* tex, SDL_Rect rect, float mass, float radius, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force) :
	name(_name), texture(tex), srcRect(rect), m_Mass(mass), m_Radius(radius), m_Position(position), m_Velocity(velocity), m_Acceleration(acceleration), m_Force(force), m_IsOnGround(false), m_CrossSectionalArea(PI * m_Radius * m_Radius), m_TakeAirResistance(TAKE_AIR_RESSISTANCE)  {}

	RigidBody(const char* _name, SDL_Texture* tex, SDL_Rect rect, float mass, float radius, Vec2 position, Vec2 velocity, Vec2 acceleration, Vec2 force, bool airResistance) :
		name(_name), texture(tex), srcRect(rect), m_Mass(mass), m_Radius(radius), m_Position(position), m_Velocity(velocity), m_Acceleration(acceleration), m_Force(force), m_IsOnGround(false), m_CrossSectionalArea(PI* m_Radius* m_Radius), m_TakeAirResistance(airResistance) {}
	RigidBody() = default;
};

