// BattleCitySFMLClone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once

#include "BattleCityManager.h"

using namespace BattleCitySFMLClone::Managers;

int main()
{	
	BattleCityManager battle_city_manager;

	battle_city_manager.Run();

    return 0;
}