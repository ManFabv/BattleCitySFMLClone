#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/RenderSystem.h"
#include "GameEngine/RenderGUISystem.h"
#include "GameEngine/AnimationSystem.h"
#include "GameEngine/MovementSystem.h"
#include "GameEngine/PlayerAnimatorControllerSystem.h"
#include "GameEngine/InputSystem.h"
#include "GameEngine/DynamicColliderSystem.h"
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
			virtual void CustomPlayerInput();
			void TakePlayerInput();
			void UpdateEntities(float dt);
			void UpdatePhysics();
			void DrawEntities();

			void LoadDrawableEntity(entt::entity entity, GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& file_name);
			void LoadAnimationInformationForEntity(entt::entity entity, const GameEngine::GameDataConfig::AnimationData& anim_data);
			void LoadMovementForEntity(entt::entity entity);
			void LoadGameFont(entt::entity entity, GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& file_name);
			void AddPlayerInputComponent(entt::entity entity);
			void LoadLevel(GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& level_json);
			void CreateTileAndAddComponents(GameEngine::DataUtils::AssetLoader& asset_loader, int atlas_size, int map_size, int tilewidth, int tileheight, int tiletype, int position_in_array, const std::string& atlas_name);

			entt::registry m_registry;
			sf::Event m_event;
			sf::RenderWindow* m_window;
			GameEngine::Systems::RenderSystem* m_render_system;
			GameEngine::Systems::RenderGUISystem* m_rendergui_system;
			GameEngine::Systems::AnimationSystem* m_anim_system;
			GameEngine::Systems::MovementSystem* m_movement_system;
			GameEngine::Systems::PlayerAnimatorControllerSystem* m_playeranimatorcontroller_system;
			GameEngine::Systems::InputSystem* m_input_system;
			GameEngine::Systems::DynamicColliderSystem* m_dynamic_collider_system;
			GameplayUtilities::Scores::ScoreManager m_score_manager;
			sf::Vector2f world_scale;
			bool m_is_paused;
		};
	}
}
