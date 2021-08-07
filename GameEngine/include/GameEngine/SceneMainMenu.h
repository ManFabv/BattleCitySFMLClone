#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/AbstractSceneBase.h"
#include "GameplayUtilities/ScoreManager.h"

namespace GameEngine
{
	namespace Scenes
	{
		class GAMEENGINE_API SceneMainMenu : public GameEngine::Scenes::AbstractSceneBase
		{
		public:
			virtual void InitializeSystems(const GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader, GameEngine::DataUtils::AssetLoader& asset_loader) override;
			virtual void CleanUpSystems() override;
		private:
			virtual void UpdateUI(float dt);
			virtual void CheckWinLoseConditions();

			virtual void CustomPlayerInput() override;
			void LoadGameFonts(entt::entity entity, GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& file_name);

			sf::Text* m_game_title_font;
			sf::Text* m_start_game_font;
		};
	}
}
