#include "GameEngine/PlayerAnimatorControllerSystem.h"

using namespace GameEngine::Systems;
using namespace GameEngine::Components;

PlayerAnimatorControllerSystem::PlayerAnimatorControllerSystem()
{
}

void PlayerAnimatorControllerSystem::Execute(entt::registry& scene_registry, float dt)
{
	auto playeranimationcontroller_view = scene_registry.view<PlayerAnimationControllerComponent, DrawableComponent, CustomPlayerInputComponent>();

	for (auto animationcontroller_entity : playeranimationcontroller_view)
	{
		PlayerAnimationControllerComponent& anim_controller = playeranimationcontroller_view.get<PlayerAnimationControllerComponent>(animationcontroller_entity);
		DrawableComponent& sprite = playeranimationcontroller_view.get<DrawableComponent>(animationcontroller_entity);
		CustomPlayerInputComponent& player_input = playeranimationcontroller_view.get<CustomPlayerInputComponent>(animationcontroller_entity);
		
		ProcessCurrentAnimationState(anim_controller, player_input);
		ProcessCurrentAnimation(anim_controller, sprite, dt);
	}
}

void PlayerAnimatorControllerSystem::ProcessCurrentAnimation(PlayerAnimationControllerComponent& player_animation_controller, DrawableComponent& drawablecomponent, float dt)
{
	AnimationComponent& anim = *player_animation_controller.current_animation;
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
	drawablecomponent.m_sprite->setTextureRect(anim.m_frames[anim.m_current_frame]);
}

void PlayerAnimatorControllerSystem::ProcessCurrentAnimationState(PlayerAnimationControllerComponent& player_animation_controller, CustomPlayerInputComponent& player_input)
{
	AnimationComponent& previous_anim = *player_animation_controller.current_animation;

	switch (previous_anim.animation_type)
	{
	case PLAYER_ANIMATION_TYPE::IDLE_UP:
	case PLAYER_ANIMATION_TYPE::IDLE_DOWN:
	case PLAYER_ANIMATION_TYPE::IDLE_LEFT:
	case PLAYER_ANIMATION_TYPE::IDLE_RIGHT:
		if (player_input.pressed_move_up)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_UP];
		else if (player_input.pressed_move_down)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_DOWN];
		else if (player_input.pressed_move_left)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_LEFT];
		else if (player_input.pressed_move_right)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_RIGHT];
		break;

	case PLAYER_ANIMATION_TYPE::MOVE_UP:
		if (!player_input.pressed_move_up && !player_input.pressed_move_down && !player_input.pressed_move_left && !player_input.pressed_move_right)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::IDLE_UP];
		else if (player_input.pressed_move_down)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_DOWN];
		else if (player_input.pressed_move_left)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_LEFT];
		else if (player_input.pressed_move_right)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_RIGHT];
		break;

	case PLAYER_ANIMATION_TYPE::MOVE_DOWN:
		if (!player_input.pressed_move_up && !player_input.pressed_move_down && !player_input.pressed_move_left && !player_input.pressed_move_right)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::IDLE_DOWN];
		else if (player_input.pressed_move_up)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_UP];
		else if (player_input.pressed_move_left)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_LEFT];
		else if (player_input.pressed_move_right)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_RIGHT];
		break;

	case PLAYER_ANIMATION_TYPE::MOVE_LEFT:
		if (!player_input.pressed_move_up && !player_input.pressed_move_down && !player_input.pressed_move_left && !player_input.pressed_move_right)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::IDLE_LEFT];
		else if (player_input.pressed_move_up)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_UP];
		else if (player_input.pressed_move_down)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_DOWN];
		else if (player_input.pressed_move_right)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_RIGHT];
		break;

	case PLAYER_ANIMATION_TYPE::MOVE_RIGHT:
		if (!player_input.pressed_move_up && !player_input.pressed_move_down && !player_input.pressed_move_left && !player_input.pressed_move_right)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::IDLE_RIGHT];
		else if (player_input.pressed_move_up)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_UP];
		else if (player_input.pressed_move_down)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_DOWN];
		else if (player_input.pressed_move_left)
			player_animation_controller.current_animation = &player_animation_controller.animations[PLAYER_ANIMATION_TYPE::MOVE_LEFT];
		break;
	}
}
