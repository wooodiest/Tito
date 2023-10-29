/// File Dependence
#include "Engine.h"
/// Internal Dependencies
#include "../Physics/RigidBody.h"
#include "../Input/Input.h"
#include "../GameObject/GameObjects.h"
#include "../Graphics/TextureManager.h"
/// External Dependencies

void Engine::AddComponents()
{
	//! Example created objects
	GameObjects::GetInstance().Add(
		"ball1",		 /// name
		Color::Pink,	 /// color
		1.0f,            /// mass
		0.1f,            /// radius
		{ 1.0f, 50.0f }, /// position
		{ 0.0f, 0.0f },  /// velocity
		{ 0.0f, 0.0f },  /// acceleration
		{ 0.0f, 0.0f },  /// force
		false			 /// taking air resistance
	);

	GameObjects::GetInstance().Add(
		"ball2",		 /// name
		Color::Orange,	 /// color
		1.0f,            /// mass
		0.1f,            /// radius
		{ 10.0f, 50.0f },/// position
		{ 0.0f, 0.0f },  /// velocity
		{ 0.0f, 0.0f },  /// acceleration
		{ 0.0f, 0.0f },  /// force
		true			 /// taking air resistance
	);
	GameObjects::GetInstance().Add(
		"ball3",		 /// name
		Color::Purple,	 /// color
		1.0f,            /// mass
		0.1f,            /// radius
		{ 20.0f, 50.0f },/// position
		{ 10.0f, 0.0f }, /// velocity
		{ 0.0f, 0.0f },  /// acceleration
		{ 0.0f, 0.0f },  /// force
		true			 /// taking air resistance
	);
}

//! Engine Properties
/// SDL
const char*		WINDOW_TITLE 					   = "Engine";
const ColorRGBA WINDOW_BACKGROUND_COLOR			   = { 124, 218, 254, 255 };
const int		WINDOW_POSITION_START_X 		   = SDL_WINDOWPOS_CENTERED;
const int		WINDOW_POSITION_START_Y 		   = SDL_WINDOWPOS_CENTERED;
const int		WINDOW_WIDTH 					   = 1280;
const int		WINDOW_HEIGHT 					   = 720;
const int		WINDOW_FULL_SCREEN 				   = 0;
const int		RENDERER_INDEX 					   = -1;
const Uint32	RENDERER_FLAGS 					   = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
/// Display Values 
float			DISPLAY_SCALE					   = 1.0f; 
const float		DISPLAY_SCALE_MIN				   = 0.1f; // 0.1 most stable
const float		DISPLAY_SCALE_MAX				   = 10.0f;
const float		DISPLAY_SCALE_STEP				   = 0.1f; // 0.1 most stable
const int		DISPLAY_MARGIN					   = 60;
float			DISPLAY_METER					   = 50.0f;
const int		MIN_SIZE_OF_TEXTURE				   = 10;
/// Coordinates system
const ColorRGBA COORDINATES_SYSTEM_AXES_COLOR	   = { 0, 0, 0, 255 };
const SDL_Color COORDINATES_SYSTEM_AXES_COLOR_TEXT = { 0, 0, 0 };
const int		COORDINATES_SYSTEM_AXES_THICKNESS  = 3; // must be odd number
const int		CAMERA_SPEED					   = 10;
/// Physic
float			TIME							   = 0.0f;
const float		PI								   = 3.14f;
const bool		DISPLAY_COLLISION_PARAMETERS	   = true;
const Vec2		GRAVITIONAL_ACCELERATION		   = {0.0f, -9.81f};
const float		ENERGY_AFTER_COLLISION			   = 0.7f;
const bool		PHISICAL_AXIS_X					   = true;
const bool		PHISICAL_AXIS_Y					   = false;
const bool		TAKE_AIR_RESSISTANCE			   = true;
const float		DRAG_COEFFICIENT				   = 0.47f;
const float		AIR_DENSITY						   = 1.225f;
//!\\\Engine Properties
//////////////////////////// Management ///////////////////////////////////
//! Start up method: Initialize SDL, creates window and renderer
void Engine::Init() 
{
	/// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) /// Check SDL was initialize successfully
	{
		SDL_Log("Failed to load SDL: %s", SDL_GetError());
		m_IsRunning = false;
		return;
	}
	/// Create Window
	m_Window = SDL_CreateWindow(
		WINDOW_TITLE,
		WINDOW_POSITION_START_X,
		WINDOW_POSITION_START_Y,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_FULL_SCREEN);

	if (!m_Window) /// Check window was created successfully
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		SDL_Quit();
		m_IsRunning = false;
		return;
	}
	/// Create Renderer
	m_Renderer = SDL_CreateRenderer(
		m_Window,
		RENDERER_INDEX,
		RENDERER_FLAGS);

	if (!m_Renderer) /// Check renderer was created successfully
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
		m_IsRunning = false;
		return;
	}
	/// Initialize SDL_ttf - text display
	TTF_Init();
	m_Font = TTF_OpenFont("assets/Roboto-Thin.ttf", 12);
	if (!m_Font) /// Check font was opened successfully
	{
		SDL_Log("Failed to open font file: %s", SDL_GetError());
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
		TTF_Quit();
		m_IsRunning = false;
		return;
	}
	/// Everything created and loaded successfully, ready to start main loop
	
	AddComponents();

	m_IsRunning = true;
}

//! Final method: Destroys window and renderer, quits SDL
void Engine::Clean()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	TTF_CloseFont(m_Font);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

//! Ends the main loop
void Engine::Quit()
{
	m_IsRunning = false;
}

///\\\\\\\\\\\\\\\\\\\\\\\ Management \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////
//////////////////////////// Main loop ////////////////////////////////////
//! Listen for Keyboard and mouse input
void Engine::Events() const
{
	Input::GetInstance().Listen();
	Camera::GetInstance().CameraController();
}

void Engine::Update(float deltaTime) const
{
	GameObjects::GetInstance().Update(deltaTime);
}

void Engine::Render() const
{
	Engine::GetInstance().DrawBackground();
	///
	Engine::GetInstance().DrawCoordinatesSystemAxes();
	Engine::GetInstance().DrawAuxilaryLines();
	///
	GameObjects::GetInstance().Render();
	///
	SDL_RenderPresent(m_Renderer);
}

///\\\\\\\\\\\\\\\\\\\\\\\ Main loop \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///
/////////////////////////////// UI ///////////////////////////////////////
//! Sets background color and clear renderer
void Engine::DrawBackground(ColorRGBA color)
{
	SDL_SetRenderDrawColor(
		m_Renderer,
		WINDOW_BACKGROUND_COLOR.r,
		WINDOW_BACKGROUND_COLOR.g,
		WINDOW_BACKGROUND_COLOR.b,
		WINDOW_BACKGROUND_COLOR.a);
	SDL_RenderClear(m_Renderer);
}

void Engine::DrawCoordinatesSystemAxes(ColorRGBA color, int thickness)
{
	SDL_SetRenderDrawColor(
		m_Renderer,
		color.r,
		color.g,
		color.b,
		color.a);

	int axeDrawValue = thickness / 2;

	for (int i = -1 * axeDrawValue; i <= axeDrawValue; i++)
	{
		SDL_RenderDrawLine(m_Renderer, Coords::X(i - 10), Coords::Y(i),Coords::X(WINDOW_WIDTH), Coords::Y(i));
		SDL_RenderDrawLine(m_Renderer, Coords::X(i), Coords::Y(i - 10), Coords::X(i), Coords::Y(WINDOW_HEIGHT));
	}
}

void Engine::DrawAuxilaryLines(ColorRGBA color, int thickness)
{
	SDL_SetRenderDrawColor(
		m_Renderer,
		color.r,
		color.g,
		color.b,
		color.a);

	int axeDrawValue = thickness / 2;
	int meterWithScale = static_cast<int>(DISPLAY_METER * DISPLAY_SCALE);
	int rangeX = WINDOW_WIDTH + Camera::x();
	int rangeY = WINDOW_HEIGHT + Camera::y();
	
	if (DISPLAY_SCALE == 0.05f)
	{
		Engine::GetInstance().DrawAuxilaryLinesL(25, axeDrawValue, meterWithScale, rangeX, rangeY);
	}
	else if (DISPLAY_SCALE < 0.25f)
	{
		Engine::GetInstance().DrawAuxilaryLinesL(10, axeDrawValue, meterWithScale, rangeX, rangeY);
	}
	else if (DISPLAY_SCALE < 1)
	{
		Engine::GetInstance().DrawAuxilaryLinesL(5, axeDrawValue, meterWithScale, rangeX, rangeY);
	}
	else
	{
		Engine::GetInstance().DrawAuxilaryLinesL(1, axeDrawValue, meterWithScale, rangeX, rangeY);
	}
}

void Engine::DrawAuxilaryLinesL(int k, int a, int m, int rX, int rY)
{
	// OX
	for (int i = m * k - Camera::x(), s = k; i <= rX; i += m * k, s += k)
	{
		if (i < 0)
			continue;

		for (int j = -1 * a; j <= a; j++)
			SDL_RenderDrawLine(m_Renderer, Coords::X(i + j), Coords::Y(5), Coords::X(i + j), Coords::Y(-5));
		Engine::GetInstance().DrawAuxilaryLinesNumbersX(i, s);
	}
	//OY
	for (int i = m * k - Camera::y(), s = k; i <= rY; i += m * k, s += k)
	{
		if (i < 0)
			continue;
		for (int j = -1 * a; j <= a; j++)
			SDL_RenderDrawLine(m_Renderer, Coords::X(-5), Coords::Y(i + j), Coords::X(5), Coords::Y(i + j));
		Engine::GetInstance().DrawAuxilaryLinesNumbersY(i, s);
	}
}

void Engine::DrawAuxilaryLinesNumbersX(int position, int scaleStep)
{
	char number[5];
	snprintf(number, sizeof(number), "%d", scaleStep);
	/// draw num on OX
	if (scaleStep < 10)
		TextureManager::GetInstance().DrawText(number, Coords::X(position - 3), Coords::Y(-7));
	else if (scaleStep < 100)
		TextureManager::GetInstance().DrawText(number, Coords::X(position - 6), Coords::Y(-7));
	else
		TextureManager::GetInstance().DrawText(number, Coords::X(position - 10), Coords::Y(-7));
}

void Engine::DrawAuxilaryLinesNumbersY(int position, int scaleStep)
{
	/// Convert num
	char number[5];
	snprintf(number, sizeof(number), "%d", scaleStep);
	/// draw num on OY
	if (scaleStep < 10)
		TextureManager::GetInstance().DrawText(number, Coords::X(-15), Coords::Y(position + 7));
	else if (scaleStep < 100)
		TextureManager::GetInstance().DrawText(number, Coords::X(-21), Coords::Y(position + 7));
	else
		TextureManager::GetInstance().DrawText(number, Coords::X(-27), Coords::Y(position + 7));
}

///\\\\\\\\\\\\\\\\\\\\\\\\\\\\ UI \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//


