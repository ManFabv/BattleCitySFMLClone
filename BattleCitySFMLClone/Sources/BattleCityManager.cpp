#include "BattleCityManager.h"
#include "GameEngine/SceneGamePlay.h"
#include "GameEngine/SceneMainMenu.h"

using namespace BattleCitySFMLClone::Managers;
using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;
using namespace GameEngine::Scenes;
using namespace GameEngine::GameManagerMain;

void BattleCityManager::Run()
{
	InitializeGame();
	StartGameLoop();
}

void BattleCityManager::InitializeGame()
{
	current_scene_index = 0;
	InitializeGameData();

	m_game_manager = new GameManager();

	m_data_loader = new ConfigLoader();
	m_asset_loader = new AssetLoader(m_game_data.config_root_folder, m_game_data.textures_folder, m_game_data.fonts_folder, m_game_data.sounds_folder);
	
	std::function<void()> m_confirmation_delegate = [&, this]() { LoadNextGameLevel(); };
	//TODO: SHOULD OPTIMIZE SCENE MANAGEMENT BECAUSE ALL SCENES ARE LOADED AT BEGINNING
	SceneMainMenu* main_menu_scene = new SceneMainMenu(m_confirmation_delegate);
	SceneGamePlay* gameplay_scene_1 = new SceneGamePlay("level_001\\Level_001.json");
	SceneGamePlay* gameplay_scene_2 = new SceneGamePlay("level_002\\Level_002.json");

	m_game_manager->InitializeSystems(&m_game_data, m_data_loader, m_asset_loader, main_menu_scene);
	m_game_manager->AddScene(gameplay_scene_1);
	m_game_manager->AddScene(gameplay_scene_2);
}

void BattleCityManager::StartGameLoop()
{
	m_game_manager->RunGameLoop();
}

void BattleCityManager::CleanGameResources()
{
	m_game_manager->CleanUpSystems();

	if (m_data_loader != nullptr)
	{
		delete m_data_loader;
		m_data_loader = nullptr;
	}
	if (m_asset_loader != nullptr)
	{
		delete m_asset_loader;
		m_asset_loader = nullptr;
	}
	if (m_game_manager != nullptr)
	{
		delete m_game_manager;
		m_game_manager = nullptr;
	}
}

void BattleCityManager::LoadNextGameLevel()
{
	current_scene_index++;
	m_game_manager->ChangeScene(current_scene_index);
	StartGameLoop();
}

void BattleCityManager::InitializeGameData()
{
	m_game_data.resX = 880;
	m_game_data.resY = 880;
	m_game_data.world_scale = 5;
	m_game_data.entities_scale = 4;
	m_game_data.window_title = "Battle City SFML Clone";
	m_game_data.config_root_folder = "assets";
	m_game_data.animations_folder = "animations";
	m_game_data.player_config = "player_anim.json";
	m_game_data.textures_folder = "textures";
	m_game_data.fonts_folder = "fonts";
	m_game_data.sounds_folder = "audio";
	m_game_data.font_name = "EndlessBossBattleRegular-v7Ey.ttf";
	m_game_data.gameplay_levels_folder_name = "levels";
}
