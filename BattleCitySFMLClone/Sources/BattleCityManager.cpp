#include "BattleCityManager.h"
#include <SFML/Graphics.hpp>

using namespace BattleCitySFMLClone::Managers;
using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;

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

	ConfigLoader data_loader;
	AssetLoader asset_loader(game_data.config_root_folder, game_data.textures_folder);
	m_game_manager.InitializeSystems(game_data, data_loader, asset_loader);
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
	game_data.textures_folder = "textures";
}
