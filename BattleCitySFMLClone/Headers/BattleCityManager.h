#pragma once

#include "GameEngine/GameManager.h"

namespace BattleCitySFMLClone
{
	namespace Managers
	{
		class BattleCityManager
		{
		public:
			void Run();
		private:
			void InitializeGame();
			void StartGameLoop();
			void CleanGameResources();

			void LoadNextGameLevel();
			void InitializeGameData();
			GameEngine::GameManagerMain::GameManager* m_game_manager;
			GameEngine::GameDataConfig::GameData m_game_data;
			GameEngine::DataUtils::ConfigLoader* m_data_loader;
			GameEngine::DataUtils::AssetLoader* m_asset_loader;
			int current_scene_index;
		};
	}
}