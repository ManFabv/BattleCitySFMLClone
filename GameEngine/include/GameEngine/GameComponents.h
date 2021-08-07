#pragma once

#include "GameEngineExportDefine.h"

#include <SFML/Graphics.hpp>

namespace GameEngine
{
	namespace Components
	{
		struct GAMEENGINE_API TransformComponent
		{
		public:
			TransformComponent(sf::Transformable& transform) : m_transform(&transform) {}
			operator sf::Transformable& () const { return *m_transform; }

			sf::Transformable* m_transform;
		};

		struct GAMEENGINE_API MovementComponent
		{
		public:
			float max_velocity = 0;
			sf::Vector2f m_velocity;
		};

		struct GAMEENGINE_API CustomPlayerInputComponent
		{
		public:
			sf::Keyboard::Key move_left;
			sf::Keyboard::Key move_right;
			sf::Keyboard::Key move_up;
			sf::Keyboard::Key move_down;
			bool pressed_move_left;
			bool pressed_move_right;
			bool pressed_move_up;
			bool pressed_move_down;
		};

		struct GAMEENGINE_API CustomMenuPlayerInputComponent
		{
		public:
			sf::Keyboard::Key move_up;
			sf::Keyboard::Key move_down;
			sf::Keyboard::Key confirm;
			bool pressed_move_up;
			bool pressed_move_down;
			bool pressed_confirm;
		};

		struct GAMEENGINE_API StaticColliderComponent
		{
		public:
			sf::FloatRect m_fixture;
		};

		struct GAMEENGINE_API DynamicColliderComponent
		{
		public:
			DynamicColliderComponent(sf::Sprite& drawable) : m_sprite(&drawable) {}
			const sf::FloatRect GetBoundingBox() const { return m_sprite->getGlobalBounds(); };
		private:
			sf::Sprite* m_sprite;
		};

		enum GAMEENGINE_API PLAYER_ANIMATION_TYPE
		{
			IDLE_UP,
			IDLE_DOWN,
			IDLE_LEFT,
			IDLE_RIGHT,
			MOVE_LEFT,
			MOVE_RIGHT,
			MOVE_UP,
			MOVE_DOWN
		};

		struct GAMEENGINE_API AnimationComponent
		{
		public:
			int m_current_frame = 0;
			float m_elapsed_time = 0;
			float m_duration = 0;
			bool m_loop = false;
			enum PLAYER_ANIMATION_TYPE animation_type;
			std::vector<sf::IntRect> m_frames;
		};

		struct GAMEENGINE_API PlayerAnimationControllerComponent
		{
		public:
			AnimationComponent* current_animation;
			std::map<PLAYER_ANIMATION_TYPE, AnimationComponent> animations;
		};

		struct GAMEENGINE_API DrawableComponent
		{
		public:
			DrawableComponent(sf::Sprite& drawable) : m_sprite(&drawable) {}
			operator const sf::Drawable& () const { return *m_sprite; }
			
			sf::Sprite* m_sprite;
		};

		struct GAMEENGINE_API DrawableFontComponent
		{
		public:
			DrawableFontComponent(sf::Text& drawable) : m_font(&drawable) {}
			operator const sf::Drawable& () const { return *m_font; }

			sf::Text* m_font;
		};
	}
}
