#pragma once

#include "GameEngineExportDefine.h"

#include <entt/entt.hpp>
#include "GameEngine/GameComponents.h"

namespace GameEngine
{
	namespace Systems
	{
		class GAMEENGINE_API PlayerAnimatorControllerSystem
		{
		public:
			PlayerAnimatorControllerSystem();
			void Execute(entt::registry& scene_registry, float dt);
		private:
			void ProcessCurrentAnimation(GameEngine::Components::PlayerAnimationControllerComponent& player_animation_controller, GameEngine::Components::DrawableComponent& drawablecomponent, float dt);
			void ProcessCurrentAnimationState(GameEngine::Components::PlayerAnimationControllerComponent& player_animation_controller, GameEngine::Components::CustomPlayerInputComponent& player_input);
		};
	}
}