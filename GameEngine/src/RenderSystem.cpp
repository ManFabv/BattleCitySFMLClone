#include "GameEngine/RenderSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void GameEngine::Systems::RenderSystem::Execute(entt::registry& scene_registry)
{
	auto render_view = scene_registry.view<DrawableComponent>();

	for (auto render_entity : render_view)
	{
		const DrawableComponent& sprite = render_view.get<DrawableComponent>(render_entity);
		m_window->draw(sprite);
	}
}
