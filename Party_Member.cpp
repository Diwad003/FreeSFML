#include "Party_Member.h"

Party_Member::Party_Member(sf::Vector2f aPosition, int aHealth, sf::Texture aTexture, int aDMG)
{
	myPosition = aPosition;
	myHealth = aHealth;
	myTexture = aTexture;
	mySprite = sf::Sprite(myTexture, sf::IntRect(sf::Vector2i(myPosition.x, myPosition.y), 
		sf::Vector2i(myTexture.getSize().x * 100, myTexture.getSize().y * 100)));
	myDMG = aDMG;
}

void Party_Member::Update()
{

}

void Party_Member::SetPosition(sf::Vector2f aMoveTo)
{
	myPosition += aMoveTo;
}

void Party_Member::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(mySprite);
}