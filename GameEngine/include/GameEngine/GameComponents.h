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
	SpriteComponent(sf::Sprite& shape) : m_shape(&shape) {}
	operator const sf::Sprite& () const { return *m_shape; }
private:
	sf::Sprite* m_shape;
};

struct GAMEENGINE_API CircleShapeComponent
{
public:
	CircleShapeComponent(sf::CircleShape& shape) : m_shape(&shape){}
	operator const sf::CircleShape& () const { return *m_shape; }
private:
	sf::CircleShape *m_shape;
};