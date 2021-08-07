#pragma once

#include "GameEngineExportDefine.h"

#include <entt/entt.hpp>
#include "GameEngine/GameComponents.h"

namespace GameEngine
{
	namespace Systems
	{
		class GAMEENGINE_API MenuCustomPlayerInputSystem
		{
		public:
			MenuCustomPlayerInputSystem(std::function<void()> confirmation_delegate):m_confirmation_delegate(confirmation_delegate){ }
			void Execute(entt::registry& scene_registry);

		private:
			std::function<void()> m_confirmation_delegate;
		};
	}
}