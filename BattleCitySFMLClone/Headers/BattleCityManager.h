#pragma once

#include "GameEngine/GameManager.h"

using namespace GameEngine::GameManagerMain;

namespace BattleCitySFMLClone
{
	namespace Managers
	{
		class BattleCityManager
		{
		public:
			BattleCityManager();
			void Run();
		private:
			void InitializeGameData(GameData& game_data);
			GameManager m_game_manager;
		};
	}
}