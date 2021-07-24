#include "GameEngine/MovementSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void MovementSystem::Execute(entt::registry& scene_registry, float dt)
{
	auto movement_view = scene_registry.view<MovementComponent, TransformComponent>();

	for (auto movement_entity : movement_view)
	{
		MovementComponent& movement = movement_view.get<MovementComponent>(movement_entity);
		if (movement.m_velocity.x != 0 || movement.m_velocity.y != 0)
		{
			sf::Vector2f movement_amount;
			movement_amount.x = movement.m_velocity.x * dt * 100;
			movement_amount.y = movement.m_velocity.y * dt * 100;
			TransformComponent& transform = movement_view.get<TransformComponent>(movement_entity);
			transform.m_transform->move(movement_amount);
		}
	}
}
