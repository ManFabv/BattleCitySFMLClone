#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/RenderSystem.h"
#include "GameplayUtilities/ScoreManager.h"

namespace GameEngine
{
	namespace GameManagerMain
	{
		struct GAMEENGINE_API GameData
		{
		public:
			int resX;
			int resY;
			std::string window_title;
			std::string config_root_folder;
			std::string animations_folder;
			std::string player_config;
		};

		class GAMEENGINE_API GameManager
		{
		public:
			void InitializeSystems(GameData& game_data);
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
