#pragma once
/// Internal Dependencies
#include "../Core/Engine.h"
/// External Dependencies
#include <chrono>
#include <thread>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DeltaTimeTracker
{
public: 
	static DeltaTimeTracker& GetInstance()
	{
		static DeltaTimeTracker instance;
		return instance;
	}

public: 
	float GetDelataTime() const { return deltaTime; }
	void Tick()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> frameDuration = currentTime - prevTime;
		prevTime = currentTime;

		deltaTime = frameDuration.count();
		TIME += deltaTime;
	}

private: 
	std::chrono::high_resolution_clock::time_point prevTime;
	float deltaTime;

private: /// singleton - hiding or deleting all initializations
	DeltaTimeTracker() :
		prevTime(std::chrono::high_resolution_clock::now()), deltaTime(0.0f) {}
	DeltaTimeTracker(const DeltaTimeTracker&) = delete;
	DeltaTimeTracker& operator=(const DeltaTimeTracker&) = delete;
	DeltaTimeTracker(DeltaTimeTracker&&) = delete;
	DeltaTimeTracker& operator=(DeltaTimeTracker&&) = delete;
	~DeltaTimeTracker() {}
};
