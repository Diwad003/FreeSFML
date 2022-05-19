#include "Party_Member.h" 

Party_Member::Party_Member()
{
}

Party_Member::Party_Member(sf::Vector2f aPosition, int aHealth, sf::Sprite aSprite, sf::Texture& aTexture, int aAbilityStrenght, Classes aClass)
{
	myPosition = aPosition;
	myHealth = aHealth;
	myTexture = aTexture;
	mySprite = aSprite;
	mySprite.setTexture(myTexture);
	mySprite.setPosition(myPosition);
	myAbilityStrenght = aAbilityStrenght;
	myClass = aClass;

	myAmoutOfEXPToNextLevel = 60;
}

void Party_Member::Update()
{

}

Entity::Classes Party_Member::GetClass()
{
	return myClass;
}

std::string Party_Member::GetClassStringRepresentation()
{
	switch (myClass)
	{
	case Entity::Classes::Healer:
		return "Healer";
		break;
	case Entity::Classes::Warrior:
		return "Warrior";
		break;
	default:
		return "ERROR";
		break;
	}
}
