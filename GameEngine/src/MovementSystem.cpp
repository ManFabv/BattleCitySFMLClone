#include "GameEngine/MovementSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void MovementSystem::Execute(entt::registry& scene_registry, float dt)
{
	auto movement_view = scene_registry.view<MovementComponent, DrawableComponent>();

	for (auto movement_entity : movement_view)
	{
		MovementComponent& movement = movement_view.get<MovementComponent>(movement_entity);
		sf::Vector2f movement_amount;
		movement_amount.x = movement.m_velocity.x * dt;
		movement_amount.y = movement.m_velocity.y * dt;
		DrawableComponent& sprite = movement_view.get<DrawableComponent>(movement_entity);
		sprite.m_sprite->move(movement_amount);
	}
}
