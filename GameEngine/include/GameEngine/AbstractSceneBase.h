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
	namespace Scenes
	{
		class GAMEENGINE_API AbstractSceneBase
		{
		public:
			virtual void InitializeSystems(const GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader, GameEngine::DataUtils::AssetLoader& asset_loader);
			void RunGameLoop();
			void PauseGame(bool pause);
			void PrepareCleanup();
			void CleanupImmediate();

		protected:
			virtual void CleanUpSystems();
			virtual void CustomPlayerInput() = 0;
			void TakePlayerInput();
			void UpdateEntities(float dt);
			void UpdatePhysics();
			void DrawEntities();
			virtual void UpdateUI(float dt) = 0;
			virtual void CheckWinLoseConditions() = 0;
			void CheckIfShouldCleanUp();

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
			bool m_prepare_cleanup;
			bool m_is_paused;

		private:
			void SetupCommonSystems(int resX, int resY, const std::string& window_title);
			void CleanupCommonSystems();
		};
	}
}
