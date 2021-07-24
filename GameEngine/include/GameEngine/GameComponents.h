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
			sf::Vector2f m_position;
		};

		struct GAMEENGINE_API MovementComponent
		{
		public:
			sf::Vector2f m_velocity;
		};

		struct GAMEENGINE_API ColliderComponent
		{
		public:
			sf::FloatRect m_fixture;
		};

		struct GAMEENGINE_API AnimationComponent
		{
		public:
			sf::IntRect m_current_subrect;
		};

		struct GAMEENGINE_API DrawableComponent
		{
		public:
			DrawableComponent(sf::Sprite& drawable) : m_sprite(&drawable) {}
			operator const sf::Drawable& () const { return *m_sprite; }
			sf::Sprite* m_sprite;
		};
	}
}
