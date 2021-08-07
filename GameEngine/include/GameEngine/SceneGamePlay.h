#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/AbstractSceneBase.h"
#include "GameplayUtilities/ScoreManager.h"

namespace GameEngine
{
	namespace Scenes
	{
		class GAMEENGINE_API SceneGamePlay : public GameEngine::Scenes::AbstractSceneBase
		{
		public:
			virtual void InitializeSystems(const GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader, GameEngine::DataUtils::AssetLoader& asset_loader) override;
			virtual void CleanUpSystems() override;
		private:
			virtual void CustomPlayerInput() override;
			virtual void UpdateUI(float dt) override;
			virtual void CheckWinLoseConditions() override;

			void LoadPlayerEntity(entt::entity entity, GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& file_name);
			void LoadEnemyEntity(entt::entity entity, GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& file_name, int posx, int posy);
			void LoadAnimationInformationForEntity(entt::entity entity, const GameEngine::GameDataConfig::AnimationData& anim_data);
			void LoadMovementForEntity(entt::entity entity);
			void LoadGameFont(entt::entity entity, GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& file_name);
			void AddPlayerInputComponent(entt::entity entity);
			void LoadLevel(GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& level_json);
			void CreateTileAndAddComponents(GameEngine::DataUtils::AssetLoader& asset_loader, int atlas_size, int map_size, int tilewidth, int tileheight, int tiletype, int position_in_array, const std::string& atlas_name);
			void UpdateScoreUI();

			GameplayUtilities::Scores::ScoreManager m_score_manager;
			sf::Vector2f world_scale;
			sf::Vector2f entities_scale;
			sf::Text* m_player_score_font;
			std::string m_user_name;
		};
	}
}
