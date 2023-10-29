#include "RigidBody.h"

std::ostream& operator<<(std::ostream& stream, const Vec2& vec2)
{
	stream << "(" << vec2.x << ", " << vec2.y << ")";
	return stream;
}

void RigidBody::Update(float deltaTime)
{
	/// acceleration += F_applied / mass + F_external / m + Gravity
	m_Acceleration = m_Force / m_Mass + GRAVITIONAL_ACCELERATION;

	if (m_TakeAirResistance)
	{
		m_Acceleration += m_Velocity * -0.5f * m_CrossSectionalArea * AIR_DENSITY * DRAG_COEFFICIENT * m_Velocity.Vec2_M() ;
	}
		
	/// velocity += acceleration * deltaTime
	m_Velocity += m_Acceleration * deltaTime;
	/// position += velocity * deltaTime
	m_Position += m_Velocity * deltaTime;
	/// Colissions
	if (m_Position.y - m_Radius <= 0.0f && PHISICAL_AXIS_X) //m_IsOnGround checks object is near ground in two next delta time. if do object is on ground and is not necessary to print info
	{
		m_Position -= m_Velocity * deltaTime;
		m_Velocity.y *= -ENERGY_AFTER_COLLISION;
		if (DISPLAY_COLLISION_PARAMETERS && !m_IsOnGround)
			DisplayParameters();
		m_IsOnGround = true;
	} 
	else
	{
		m_IsOnGround = false;
	}
	if (m_Position.x - m_Radius<= 0.0f && PHISICAL_AXIS_Y)
	{
		m_Position -= m_Velocity * deltaTime;
		m_Velocity.x *= -ENERGY_AFTER_COLLISION;
		if (DISPLAY_COLLISION_PARAMETERS)
			DisplayParameters();
	}
}

void RigidBody::Render()
{
	TextureManager::GetInstance().DrawCircleWithScale(texture, srcRect, m_Position.x, m_Position.y, m_Radius);
}

void RigidBody::ApplyForce(Vec2 force)
{

}

void RigidBody::DisplayParameters()
{
	std::cout << "name         - " << name << std::endl;
	std::cout << "mass         - " << m_Mass <<"kg" << std::endl;
	std::cout << "radius       - " << m_Radius <<"m" << std::endl;
	std::cout << "time         - " << TIME << "s" << std::endl;
	std::cout << "position     - " << m_Position << "m" << std::endl;
	std::cout << "velocity     - " << m_Velocity <<"m/s" << std::endl;
	std::cout << "acceleration - " << m_Acceleration <<"m/s^2" << std::endl;
	std::cout << "force        - " << m_Force <<"N" << std::endl;
	std::cout << std::endl;
}
