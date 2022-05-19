#include "Entity.h"

Entity::Entity()
{
}

void Entity::TakeDamage(int aDMG)
{
	myHealth -= aDMG;
}

void Entity::Heal(int aHealStrenght)
{
	myHealth += aHealStrenght;
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

int Entity::GetAbilityStrenght()
{
	return myAbilityStrenght;
}

int Entity::GetHealth()
{
	return myHealth;
}

int Entity::GetLevel()
{
	return myLevel;
}

void Entity::AddToEXP(int& aEXP)
{
	myEXP += aEXP;
}

void Entity::LevelUp()
{
	while (myEXP >= myAmoutOfEXPToNextLevel)
	{
		if (myEXP >= myAmoutOfEXPToNextLevel)
		{
			myLevel++;
			myEXP -= myAmoutOfEXPToNextLevel;
		}
	}
}