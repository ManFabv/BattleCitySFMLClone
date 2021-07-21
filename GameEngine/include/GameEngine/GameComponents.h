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

struct GAMEENGINE_API DrawableComponent
{
public:
	DrawableComponent(sf::Drawable& drawable) : m_drawable(&drawable) {}
	operator const sf::Drawable& () const { return *m_drawable; }
protected:
	sf::Drawable* m_drawable;
};