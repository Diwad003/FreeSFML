#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(sf::Vector2f aPosition, int aHealth, sf::Sprite aSprite, int aDMG)
{
	myPosition = aPosition;
	myHealth = aHealth;
	mySprite = aSprite;
	myDMG = aDMG;
}

void Entity::TakeDamage(int aDMG)
{
	myHealth -= aDMG;
}