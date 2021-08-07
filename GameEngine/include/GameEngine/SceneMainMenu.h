#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/AbstractSceneBase.h"
#include "GameEngine/MenuCustomPlayerInputSystem.h"

namespace GameEngine
{
	namespace Scenes
	{
		class GAMEENGINE_API SceneMainMenu : public GameEngine::Scenes::AbstractSceneBase
		{
		public:
			SceneMainMenu(std::function<void()> confirmation_delegate) :m_confirmation_delegate(confirmation_delegate) { }
			virtual void InitializeSystems(const GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader, GameEngine::DataUtils::AssetLoader& asset_loader) override;
			virtual void CleanUpSystems() override;
		private:
			virtual void UpdateUI(float dt);
			virtual void CheckWinLoseConditions();

			virtual void CustomPlayerInput() override;
			void LoadGameFonts(entt::entity entity_title, entt::entity entity_start, GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& file_name);

			sf::Text* m_game_title_font;
			sf::Text* m_start_game_font;
			GameEngine::Systems::MenuCustomPlayerInputSystem* m_menu_player_input_system;
			std::function<void()> m_confirmation_delegate;
		};
	}
}
