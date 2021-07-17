// BattleCitySFMLClone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GameEngine/GameManager.h"
#include <Windows.h>

using namespace GameEngine::GameManagerMain;

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	GameManager game_manager;

	game_manager.TestGameEngineImplementation();

    return 0;
}