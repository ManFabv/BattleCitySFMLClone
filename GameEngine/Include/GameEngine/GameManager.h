#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/RenderSystem.h"
#include "GameplayUtilities/ScoreManager.h"
#include "GameEngine/ConfigLoader.h"
#include "GameEngine/GameData.h"
#include "GameEngine/AssetLoader.h"

namespace GameEngine
{
	namespace GameManagerMain
	{
		class GAMEENGINE_API GameManager
		{
		public:
			void InitializeSystems(const GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader, GameEngine::DataUtils::AssetLoader& asset_loader);
			void RunGameLoop();
			void CleanUpSystems();
			void PauseGame(bool pause);
		private:
			void TakePlayerInput();
			void UpdateEntities(float dt);
			void DrawEntities();
			void UpdateGUI();
			void DrawGUI();

			void LoadDrawableEntity(GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& root_folder, const std::string& config_folder, const std::string& file_name);

			entt::registry m_registry;
			sf::Event m_event;
			sf::RenderWindow* m_window;
			GameEngine::Systems::RenderSystem* m_render_system;
			GameplayUtilities::Scores::ScoreManager m_score_manager;
			bool m_is_paused;
		};
	}
}
