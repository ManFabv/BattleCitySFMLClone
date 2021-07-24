#include "GameEngine/AnimationSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void AnimationSystem::Execute(entt::registry& scene_registry, float dt)
{
	auto animation_view = scene_registry.view<AnimationComponent, DrawableComponent>();

	for (auto anim_entity : animation_view)
	{
		AnimationComponent& anim = animation_view.get<AnimationComponent>(anim_entity);
		anim.m_elapsed_time += dt;
		if (anim.m_elapsed_time >= anim.m_duration)
		{
			anim.m_current_frame++;
			if (anim.m_current_frame >= anim.m_frames.size())
			{
				anim.m_elapsed_time = 0;
				if (anim.m_loop)
					anim.m_current_frame = 0;
				else
					anim.m_current_frame--;
			}
			
		}
		DrawableComponent& sprite = animation_view.get<DrawableComponent>(anim_entity);
		sprite.m_sprite->setTextureRect(anim.m_frames[anim.m_current_frame]);
	}
}
