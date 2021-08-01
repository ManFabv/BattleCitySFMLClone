#include "GameEngine/DynamicColliderSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void DynamicColliderSystem::Execute(entt::registry& scene_registry)
{
	auto dynamic_collider_view = scene_registry.view<TransformComponent, DynamicColliderComponent, MovementComponent>();
	auto static_collider_view = scene_registry.view<StaticColliderComponent>();

	for (auto dynamic_collider_entity : dynamic_collider_view)
	{
		DynamicColliderComponent& dynamic_collider = dynamic_collider_view.get<DynamicColliderComponent>(dynamic_collider_entity);
		TransformComponent& dynamic_tranform = dynamic_collider_view.get<TransformComponent>(dynamic_collider_entity);
		MovementComponent& dynamic_movement = dynamic_collider_view.get<MovementComponent>(dynamic_collider_entity);

		for (auto static_collider_entity : static_collider_view)
		{
			const StaticColliderComponent& static_collider = static_collider_view.get<StaticColliderComponent>(static_collider_entity);
			const sf::FloatRect static_fixture = static_collider.m_fixture;
			const sf::FloatRect dynamic_fixture = dynamic_collider.GetBoundingBox();
			sf::FloatRect intersection;
			if (dynamic_fixture.intersects(static_collider.m_fixture, intersection))
			{
				float movex = 0;
				float movey = 0;
				if (dynamic_movement.m_velocity.x > 0)
				{
					movex = -intersection.width;
				}
				else if (dynamic_movement.m_velocity.x < 0)
				{
					movex = intersection.width;
				}
				else if (dynamic_movement.m_velocity.y > 0)
				{
					movey = -intersection.height;
				}
				else if (dynamic_movement.m_velocity.y < 0)
				{
					movey = intersection.height;
				}
				dynamic_tranform.m_transform->move(movex, movey);
			}
		}
	}
}