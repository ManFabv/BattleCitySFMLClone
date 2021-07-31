#include "GameEngine/InputSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void InputSystem::Execute(entt::registry& scene_registry)
{
	auto input_view = scene_registry.view<CustomPlayerInputComponent, MovementComponent>();

	for (auto input_entity : input_view)
	{
		CustomPlayerInputComponent& input = input_view.get<CustomPlayerInputComponent>(input_entity);
		MovementComponent& movement = input_view.get<MovementComponent>(input_entity);
		input.pressed_move_left = false;
		input.pressed_move_right = false;
		input.pressed_move_up = false;
		input.pressed_move_down = false;

		if (sf::Keyboard::isKeyPressed(input.move_left))
		{
			movement.m_velocity.x = -1 * movement.max_velocity;
			movement.m_velocity.y = 0;
			input.pressed_move_left = true;
		}
		else if (sf::Keyboard::isKeyPressed(input.move_right))
		{
			movement.m_velocity.x = 1 * movement.max_velocity;
			movement.m_velocity.y = 0;
			input.pressed_move_right = true;
		}
		else if (sf::Keyboard::isKeyPressed(input.move_up))
		{
			movement.m_velocity.y = -1 * movement.max_velocity;
			movement.m_velocity.x = 0;
			input.pressed_move_up = true;
		}
		else if (sf::Keyboard::isKeyPressed(input.move_down))
		{
			movement.m_velocity.y = 1 * movement.max_velocity;
			movement.m_velocity.x = 0;
			input.pressed_move_down = true;
		}
		else
		{
			movement.m_velocity = sf::Vector2f(0, 0);
		}
	}
}
