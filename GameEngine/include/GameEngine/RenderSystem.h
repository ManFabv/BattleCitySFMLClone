#pragma once

#include "GameEngineExportDefine.h"

#include <entt/entt.hpp>
#include "GameEngine/GameComponents.h"

namespace GameEngine
{
	namespace Systems
	{
		class GAMEENGINE_API RenderSystem
		{
		public:
			RenderSystem(sf::RenderWindow &current_window) : m_window(&current_window) {}
			void Execute(entt::registry& scene_registry);
		private:
			sf::RenderWindow *m_window;
		};
	}
}