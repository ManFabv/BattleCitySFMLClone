#include "GameEngine/InputSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void InputSystem::Execute(entt::registry& scene_registry)
{
	auto input_view = scene_registry.view<CustomPlayerInputComponent, MovementComponent>();

	for (auto input_entity : input_view)
	{
		const CustomPlayerInputComponent& input = input_view.get<CustomPlayerInputComponent>(input_entity);
		MovementComponent& movement = input_view.get<MovementComponent>(input_entity);
		movement.m_velocity = sf::Vector2f(0, 0);

		if (sf::Keyboard::isKeyPressed(input.move_left))
			movement.m_velocity.x = -1 * movement.max_velocity;
		if (sf::Keyboard::isKeyPressed(input.move_right))
			movement.m_velocity.x = 1 * movement.max_velocity;
		if (sf::Keyboard::isKeyPressed(input.move_up))
			movement.m_velocity.y = -1 * movement.max_velocity;
		if (sf::Keyboard::isKeyPressed(input.move_down))
			movement.m_velocity.y = 1 * movement.max_velocity;
	}
}
