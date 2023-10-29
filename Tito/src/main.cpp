/// Internal Dependencies
#include "Core/Engine.h"
#include "Time/DeltaTimeTracker.h"
#include <SDL_ttf.h>
/// External Dependencies

int main(int argc, char* argv[])
{
	/// Initialize and creates window
	Engine::GetInstance().Init();
	/// Main loop
	while (Engine::GetInstance().IsRunning())
	{
		Engine::GetInstance().Events();
		Engine::GetInstance().Update(DeltaTimeTracker::GetInstance().GetDelataTime());
		Engine::GetInstance().Render();
		/// Calculating time difference between frames
		DeltaTimeTracker::GetInstance().Tick();
	}
	/// Destroying window, renderer, quits SDL
	Engine::GetInstance().Clean();

	return 0;
}