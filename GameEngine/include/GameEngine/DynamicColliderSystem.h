#pragma once

#include "GameEngineExportDefine.h"

#include <entt/entt.hpp>
#include "GameEngine/GameComponents.h"

namespace GameEngine
{
	namespace Systems
	{
		class GAMEENGINE_API DynamicColliderSystem
		{
		public:
			DynamicColliderSystem(float ignore_collision_threshold) :m_ignore_collision_threshold(ignore_collision_threshold) {}
			void Execute(entt::registry& scene_registry);

		private:
			float m_ignore_collision_threshold;
		};
	}
}
