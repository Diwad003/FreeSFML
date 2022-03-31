#include "Enemy_Party_Member.h"
#include <iostream>

Enemy_Party_Member::Enemy_Party_Member(sf::Vector2f aPosition, int aHealth, sf::Sprite aSprite, sf::Texture& aTexture, int aDMG, std::vector<Party_Member*> &aPlayerParty,
	Classes aClass)
{
	myPosition = aPosition;
	myHealth = aHealth;
	myTexture = aTexture;
	mySprite = aSprite;
	mySprite.setTexture(myTexture);
	mySprite.setPosition(myPosition);
	myDMG = aDMG;
	myPlayerParty = aPlayerParty;
	myClass = aClass;
}

void Enemy_Party_Member::Update()
{
	sf::IntRect r1 = mySprite.getTextureRect();
	sf::IntRect r2 = myPlayerParty[0]->GetSprite().getTextureRect();

	if (myPosition.x <= myPlayerParty[0]->GetPosition().x + r2.width && myPosition.x + r1.width >= myPlayerParty[0]->GetPosition().x)
	{
		myTimeForBattle = true;
	}
}

bool Enemy_Party_Member::GetTimeForBattle()
{
	return myTimeForBattle;
}
