#include "BattleCityManager.h"

using namespace BattleCitySFMLClone::Managers;

BattleCitySFMLClone::Managers::BattleCityManager::~BattleCityManager()
{
	CleanGameResources();
}

void BattleCityManager::Run()
{
	InitializeGame();
	StartGameLoop();
}

void BattleCityManager::InitializeGame()
{
	GameData game_data;
	InitializeGameData(game_data);

	m_game_manager.InitializeSystems(game_data);
}

void BattleCitySFMLClone::Managers::BattleCityManager::StartGameLoop()
{
	m_game_manager.RunGameLoop();
}

void BattleCitySFMLClone::Managers::BattleCityManager::CleanGameResources()
{
	m_game_manager.CleanUpSystems();
}

void BattleCityManager::InitializeGameData(GameData& game_data)
{
	game_data.resX = 800;
	game_data.resY = 800;
	game_data.window_title = "Battle City SFML Clone";
	game_data.config_root_folder = "assets";
	game_data.animations_folder = "animations";
	game_data.player_config = "player_anim.json";
}
