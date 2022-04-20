#include "Entity.h"

Entity::Entity()
{
}

void Entity::TakeDamage(int aDMG)
{
	myHealth -= aDMG;
}

void Entity::SetPosition(sf::Vector2f aMoveTo)
{
	myPosition += aMoveTo;
	mySprite.setPosition(myPosition);
}

void Entity::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(mySprite);
}

sf::Vector2f Entity::GetPosition()
{
	return myPosition;
}

sf::Sprite Entity::GetSprite()
{
	return mySprite;
}

int Entity::GetDamage()
{
	return myDMG;
}

int Entity::GetHealth()
{
	return myHealth;
}
