#include "GameEngine/GameManager.h"

using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;
using namespace GameEngine::GameManagerMain;

GameManager::GameManager()
{
	m_current_scene = nullptr;
}

void GameManager::AddScene(GameEngine::Scenes::AbstractSceneBase* new_scene)
{
	m_scenes.push_back(new_scene);

	if (m_current_scene == nullptr)
		m_current_scene = m_scenes[0];
}

void GameManager::ChangeScene(int scene_id)
{
	if (m_current_scene != nullptr)
		m_current_scene->PrepareCleanup();

	m_current_scene = m_scenes[scene_id];

	m_current_scene->InitializeSystems(*m_game_data, *m_config_loader, *m_asset_loader, m_window);
}

void GameManager::InitializeSystems(GameData* game_data, ConfigLoader* config_loader, AssetLoader* asset_loader, GameEngine::Scenes::AbstractSceneBase* initial_scene)
{
	m_game_data = game_data;
	m_config_loader = config_loader;
	m_asset_loader = asset_loader;

	m_window = new sf::RenderWindow(sf::VideoMode(m_game_data->resX, m_game_data->resY), m_game_data->window_title);
	m_window->setVerticalSyncEnabled(true);

	AddScene(initial_scene);

	m_current_scene->InitializeSystems(*m_game_data, *m_config_loader, *m_asset_loader, m_window);
}

void GameManager::RunGameLoop()
{
	m_current_scene->RunGameLoop();
}

void GameManager::CleanUpSystems()
{
	for (auto* scene : m_scenes)
	{
		if (scene != nullptr)
		{
			scene->CleanupImmediate();
			delete scene;
			scene = nullptr;
		}
	}
	m_scenes.clear();

	if (m_window != nullptr)
	{
		delete m_window;
		m_window = nullptr;
	}
}

void GameManager::PauseGame(bool pause)
{
	m_current_scene->PauseGame(pause);
}
