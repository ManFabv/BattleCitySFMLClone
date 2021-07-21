// BattleCitySFMLClone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#include "GameEngine/GameManager.h"

using namespace GameEngine::GameManagerMain;

int main()
{	
	GameManager game_manager;

	game_manager.InitializeSystems(800, 800, "SFML works!");
	game_manager.RunGameLoop();
	game_manager.CleanUpSystems();

    return 0;
}