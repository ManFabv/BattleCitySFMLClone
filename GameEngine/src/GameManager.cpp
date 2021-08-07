#include "GameEngine/GameManager.h"

using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;
using namespace GameEngine::GameManagerMain;

GameManager::GameManager()
{
	m_current_scene = nullptr;
}

GameManager::~GameManager()
{
	CleanUpSystems();
}

void GameManager::AddScene(GameEngine::Scenes::AbstractSceneBase* new_scene)
{
	m_scenes.push_back(new_scene);

	if (m_current_scene == nullptr)
		ChangeScene(0);
}

void GameManager::ChangeScene(int scene_id)
{
	m_current_scene = m_scenes[scene_id];
}

void GameManager::InitializeSystems(const GameData& game_data, ConfigLoader& config_loader, AssetLoader& asset_loader, GameEngine::Scenes::AbstractSceneBase* initial_scene)
{
	AddScene(initial_scene);

	m_current_scene->InitializeSystems(game_data, config_loader, asset_loader);
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
			scene->CleanUpSystems();
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
