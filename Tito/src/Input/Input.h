#pragma once
/// Internal Dependencies
#include "../Core/Engine.h"
/// External Dependencies
#include <SDL.h>
#include <cmath>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Input
{
public: /// singleton instance
	static Input& GetInstance()
	{
		static Input instance;
		return instance;
	}

public: 
	void Listen();
	bool GetKeyDown(SDL_Scancode key) const;
	

private: 
	void GetKeyBoardSates()
	{
		m_KeyStates = SDL_GetKeyboardState(nullptr);
	}

private: 
	const Uint8* m_KeyStates;

private: /// singleton - hiding or deleting all initializations
	Input()
	{
		m_KeyStates = SDL_GetKeyboardState(nullptr);
	}
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	Input(Input&&) = delete;
	Input& operator=(Input&&) = delete;
	~Input() {}
};