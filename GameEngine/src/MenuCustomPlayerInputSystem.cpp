#include "GameEngine/MenuCustomPlayerInputSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void MenuCustomPlayerInputSystem::Execute(entt::registry& scene_registry)
{
	auto input_view = scene_registry.view<CustomMenuPlayerInputComponent>();

	for (auto input_entity : input_view)
	{
		CustomMenuPlayerInputComponent& input = input_view.get<CustomMenuPlayerInputComponent>(input_entity);
		input.pressed_confirm = false;
		input.pressed_move_up = false;
		input.pressed_move_down = false;

		//TODO: THIS SHOULD BE BETTER IF WE USE SF::EVENTS INSTEAD TO AVOID LOSING ANY KEY PRESS
		if (sf::Keyboard::isKeyPressed(input.confirm))
		{
			input.pressed_confirm = true;
			m_confirmation_delegate();
		}
		else if (sf::Keyboard::isKeyPressed(input.move_up))
		{
			input.pressed_move_up = true;
		}
		else if (sf::Keyboard::isKeyPressed(input.move_down))
		{
			input.pressed_move_down = true;
		}
	}
}
