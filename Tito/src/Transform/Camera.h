#pragma once

#include "../Input/Input.h"
#include "../Core/Engine.h"
#include <SDL.h>

class Camera
{
public: /// singleton instance
	static Camera& GetInstance()
	{
		static Camera instance;
		return instance;
	}
public:
	void CameraController();
	static int x() { return GetInstance().X; }
	static int y() { return GetInstance().Y; }
	void Reset()
	{
		X = 0;
		Y = 0;
	}
public:
	int X, Y;

private: /// singleton - hiding or deleting all initializations
	Camera() :
		X(0), Y(0) {}
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(Camera&&) = delete;
	~Camera() {}

};



