#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/RenderSystem.h"
#include "GameplayUtilities/ScoreManager.h"

namespace GameEngine
{
	namespace GameManagerMain
	{
		static class GAMEENGINE_API GameManager
		{
		public:
			void InitializeSystems(entt::registry& registry, sf::RenderWindow& window);
			void RunGameLoop();
			void CleanUpSystems();
		private:
			void TakePlayerInput();
			void UpdateEntities();
			void DrawEntities();

			entt::registry *m_registry;
			sf::Event m_event;
			sf::RenderWindow *m_window;
			
			GameEngine::Systems::RenderSystem *m_render_system;

			GameplayUtilities::Scores::ScoreManager m_score_manager;
		};
	}
}
