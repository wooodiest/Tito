#pragma once
/// Internal Dependencies
#include "../Transform/Camera.h"
#include "../Graphics/Color.h"
#include "../Transform/Coordinates.h"
#include "../Math/Vec2.h"
/// External Dependencies
#include <SDL_ttf.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
//! Engine Properties
/// SDL
extern const char* WINDOW_TITLE;
extern const ColorRGBA WINDOW_BACKGROUND_COLOR;
extern const int WINDOW_POSITION_START_X;
extern const int WINDOW_POSITION_START_Y;
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int WINDOW_FULL_SCREEN;
extern const int RENDERER_INDEX;
extern const Uint32 RENDERER_FLAGS;
/// Display Values
extern float DISPLAY_SCALE;
extern const float DISPLAY_SCALE_MIN;
extern const float DISPLAY_SCALE_MAX;
extern const float DISPLAY_SCALE_STEP;
extern const int DISPLAY_MARGIN;
extern float DISPLAY_METER;
extern const int MIN_SIZE_OF_TEXTURE;
/// Coordinates system
extern const ColorRGBA COORDINATES_SYSTEM_AXES_COLOR;
extern const SDL_Color COORDINATES_SYSTEM_AXES_COLOR_TEXT;
extern const int COORDINATES_SYSTEM_AXES_THICKNESS;
extern const int CAMERA_SPEED;
/// Physic
extern float TIME;
extern const float PI;
extern const bool DISPLAY_COLLISION_PARAMETERS;
extern const Vec2 GRAVITIONAL_ACCELERATION;
extern const float ENERGY_AFTER_COLLISION;
extern const bool PHISICAL_AXIS_X;
extern const bool PHISICAL_AXIS_Y;
extern const bool TAKE_AIR_RESSISTANCE;
extern const float DRAG_COEFFICIENT;
extern const float AIR_DENSITY;
//!\\\Engine Properties
//////////////////////////////////////////////////////////////////////////
class Engine
{
public: /// singleton instance
	static Engine& GetInstance()
	{
		static Engine instance;
		return instance;
	}
public: 
	/// Management
	void AddComponents();
	void Init();
	void Clean();
	void Quit();
	/// Main loop
	void Events() const;
	void Update(float deltaTime) const;
	void Render() const;
	/// UI
	void DrawBackground(ColorRGBA color = WINDOW_BACKGROUND_COLOR);
	void DrawCoordinatesSystemAxes(ColorRGBA color = COORDINATES_SYSTEM_AXES_COLOR, int thickness = COORDINATES_SYSTEM_AXES_THICKNESS);
	void DrawAuxilaryLines(ColorRGBA color = COORDINATES_SYSTEM_AXES_COLOR, int thickness = COORDINATES_SYSTEM_AXES_THICKNESS);
	void DrawAuxilaryLinesL(int k, int a, int m, int rX, int rY);
	void DrawAuxilaryLinesNumbersX(int position, int scaleStep);
	void DrawAuxilaryLinesNumbersY(int position, int scaleStep);
	/// Getters
	bool IsRunning() const { return m_IsRunning; }
	SDL_Renderer* GetRenderer() { return m_Renderer; }
	TTF_Font* GetFont() { return m_Font; }

private: 
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	TTF_Font* m_Font;
	bool m_IsRunning;;

private: /// singleton - hiding or deleting all initializations
	Engine() :
		m_Window(nullptr), m_Renderer(nullptr),m_Font(nullptr), m_IsRunning(false) {}
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator=(Engine&&) = delete;
	~Engine() {}
};

