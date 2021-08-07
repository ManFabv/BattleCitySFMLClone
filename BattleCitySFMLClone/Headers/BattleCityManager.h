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

			void StartGame();
			void InitializeGameData(GameEngine::GameDataConfig::GameData& game_data);
			GameEngine::GameManagerMain::GameManager m_game_manager;
		};
	}
}