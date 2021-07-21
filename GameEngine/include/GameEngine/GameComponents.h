#include <SFML/Graphics.hpp>
#include "GameEngineExportDefine.h"

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

struct GAMEENGINE_API SpriteComponent
{
public:
	sf::Sprite m_sprite;

	operator const sf::Sprite& () const { return m_sprite; }
};

struct GAMEENGINE_API CircleShapeComponent
{
public:
	sf::CircleShape m_shape;

	operator const sf::CircleShape& () const { return m_shape; }
};