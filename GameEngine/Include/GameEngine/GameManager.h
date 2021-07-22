#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/RenderSystem.h"
#include "GameplayUtilities/ScoreManager.h"
#include "GameEngine/ConfigLoader.h"

namespace GameEngine
{
	namespace GameManagerMain
	{
		class GAMEENGINE_API GameManager
		{
		public:
			void InitializeSystems(const GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader);
			void RunGameLoop();
			void CleanUpSystems();
		private:
			void TakePlayerInput();
			void UpdateEntities();
			void DrawEntities();

			entt::registry m_registry;
			sf::Event m_event;
			sf::RenderWindow* m_window;
			GameEngine::Systems::RenderSystem* m_render_system;
			GameplayUtilities::Scores::ScoreManager m_score_manager;
		};
	}
}
