#include "Party_Member.h" 

Party_Member::Party_Member(sf::Vector2f aPosition, int aHealth, sf::Sprite aSprite, sf::Texture& aTexture, int aDMG)
{
	myPosition = aPosition;
	myHealth = aHealth;
	myTexture = aTexture;
	mySprite = aSprite;
	mySprite.setTexture(myTexture);
	mySprite.setPosition(myPosition);
	myDMG = aDMG;
}

void Party_Member::Update()
{

}