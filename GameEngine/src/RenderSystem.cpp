#include "GameEngine\RenderSystem.h"
#include "GameEngine\GameComponents.h"

using namespace GameEngine::Systems;

GameEngine::Systems::RenderSystem::RenderSystem(sf::RenderWindow &current_window) : m_window(&current_window)
{
}

void GameEngine::Systems::RenderSystem::Execute(entt::registry& scene_registry)
{
	auto render_view = scene_registry.view<DrawableComponent>();

	for (auto render_entity : render_view)
	{
		const DrawableComponent& sprite = render_view.get<DrawableComponent>(render_entity);
		m_window->draw(sprite);
	}
}
