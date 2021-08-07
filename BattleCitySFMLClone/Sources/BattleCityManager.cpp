#include "BattleCityManager.h"
#include "GameEngine/SceneGamePlay.h"
#include "GameEngine/SceneMainMenu.h"

using namespace BattleCitySFMLClone::Managers;
using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;
using namespace GameEngine::Scenes;

BattleCityManager::~BattleCityManager()
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
	AssetLoader asset_loader(game_data.config_root_folder, game_data.textures_folder, game_data.fonts_folder, game_data.sounds_folder);
	
	SceneMainMenu* main_menu_scene = new SceneMainMenu();
	SceneGamePlay* gameplay_scene = new SceneGamePlay();

	m_game_manager.InitializeSystems(game_data, data_loader, asset_loader, gameplay_scene);
	m_game_manager.AddScene(gameplay_scene);
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
	game_data.resX = 880;
	game_data.resY = 880;
	game_data.world_scale = 5;
	game_data.entities_scale = 4;
	game_data.window_title = "Battle City SFML Clone";
	game_data.config_root_folder = "assets";
	game_data.animations_folder = "animations";
	game_data.player_config = "player_anim.json";
	game_data.textures_folder = "textures";
	game_data.fonts_folder = "fonts";
	game_data.sounds_folder = "audio";
	game_data.font_name = "EndlessBossBattleRegular-v7Ey.ttf";
	game_data.gameplay_level_name = "level_001\\Level_001.json";
	game_data.gameplay_levels_folder_name = "levels";
}
