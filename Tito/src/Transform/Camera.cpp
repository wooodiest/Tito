#include "Camera.h"

void Camera::CameraController()
{
	if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_A))
	{
		X -= CAMERA_SPEED;
		if (X < 0)
			X = 0;
	}
		
	if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_D))
	{
		X += CAMERA_SPEED;
	}

	if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_W))
	{
		Y += CAMERA_SPEED;
	}
	if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_S))
	{
		Y -= CAMERA_SPEED;
		if (Y < 0)
			Y = 0;
	}
	if (Input::GetInstance().GetKeyDown(SDL_SCANCODE_LSHIFT))
	{
		X = 0;
		Y = 0;
	}
		
}
