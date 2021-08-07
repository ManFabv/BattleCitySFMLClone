#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/ConfigLoader.h"
#include "GameEngine/GameData.h"
#include "GameEngine/AssetLoader.h"
#include "GameEngine/AbstractSceneBase.h"
#include <vector>

namespace GameEngine
{
	namespace GameManagerMain
	{
		class GAMEENGINE_API GameManager
		{
		public:
			GameManager();
			void AddScene(GameEngine::Scenes::AbstractSceneBase* new_scene);
			void ChangeScene(int scene_id);
			void InitializeSystems(GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader, GameEngine::DataUtils::AssetLoader& asset_loader, GameEngine::Scenes::AbstractSceneBase* initial_scene);
			void RunGameLoop();
			void CleanUpSystems();
			void PauseGame(bool pause);

		private:
			std::vector<GameEngine::Scenes::AbstractSceneBase*> m_scenes;
			GameEngine::Scenes::AbstractSceneBase* m_current_scene;

			GameEngine::GameDataConfig::GameData* m_game_data;
			GameEngine::DataUtils::ConfigLoader* m_config_loader;
			GameEngine::DataUtils::AssetLoader* m_asset_loader;
		};
	}
}
