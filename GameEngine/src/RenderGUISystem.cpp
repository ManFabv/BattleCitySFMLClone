#include "GameEngine/RenderGUISystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void RenderGUISystem::Execute(entt::registry& scene_registry)
{
	auto render_view = scene_registry.view<DrawableFontComponent>();

	for (auto render_entity : render_view)
	{
		const DrawableFontComponent& font = render_view.get<DrawableFontComponent>(render_entity);
		m_window->draw(font);
	}
}
