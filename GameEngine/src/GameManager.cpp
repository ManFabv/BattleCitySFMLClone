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
		ChangeScene(0);
}

void GameManager::ChangeScene(int scene_id)
{
	if (m_current_scene != nullptr)
		m_current_scene->PrepareCleanup();

	m_current_scene = m_scenes[scene_id];

	m_current_scene->InitializeSystems(*m_game_data, *m_config_loader, *m_asset_loader);
}

void GameManager::InitializeSystems(GameData* game_data, ConfigLoader* config_loader, AssetLoader* asset_loader, GameEngine::Scenes::AbstractSceneBase* initial_scene)
{
	m_game_data = game_data;
	m_config_loader = config_loader;
	m_asset_loader = asset_loader;

	AddScene(initial_scene);

	m_current_scene->InitializeSystems(*m_game_data, *m_config_loader, *m_asset_loader);
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
}

void GameManager::PauseGame(bool pause)
{
	m_current_scene->PauseGame(pause);
}
