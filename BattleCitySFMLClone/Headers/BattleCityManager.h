#pragma once

#include "GameEngine/GameManager.h"

namespace BattleCitySFMLClone
{
	namespace Managers
	{
		class BattleCityManager
		{
		public:
			~BattleCityManager();
			void Run();
		private:
			void InitializeGame();
			void StartGameLoop();
			void CleanGameResources();

			void InitializeGameData(GameEngine::GameManagerMain::GameData& game_data);
			GameEngine::GameManagerMain::GameManager m_game_manager;
		};
	}
}