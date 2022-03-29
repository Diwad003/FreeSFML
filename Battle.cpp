#include "Battle.h"

Battle::Battle(std::vector<Party_Member*>& aPartyMembers, std::vector<Enemy_Party_Member*>& aEnemyPartyMembers, sf::Sprite& aWallSprite)
{
	myPlayerPartyMembers = aPartyMembers;
	myEnemyPartyMembers = aEnemyPartyMembers;
	myWallSprite = aWallSprite;
	myPlayerTurn = true;


	myFont.loadFromFile("arial.ttf");
	myText.setFont(myFont);
	myText.setCharacterSize(24);
	myText.setFillColor(sf::Color::Black);


	sf::Vector2f tempPosition = sf::Vector2f(1000, 691);
	for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
	{
		if (i > 0)
		{
			tempPosition.x += myPlayerPartyMembers[i - 1]->GetSprite().getScale().x;
		}
		myPlayerPartyMembers[i]->SetPosition(tempPosition);
	}

	tempPosition = sf::Vector2f(2000, 691);
	for (size_t i = 0; i < myEnemyPartyMembers.size(); i++)
	{
		if (i > 0)
		{
			tempPosition.x += myEnemyPartyMembers[i - 1]->GetSprite().getScale().x;
		}
		myEnemyPartyMembers[i]->SetPosition(tempPosition);
	}
}

void Battle::BattleLogic(sf::RenderWindow& aWindow)
{
	if (myPlayerTurn)
	{
		while (true)
		{
			myText.setString("You are in a battle with the enemy, press on the respective number for the action you want to do:\n"
				"1: Attack\n2: Defend\n3: Heal\n4: Use abilities");

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{


				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{


				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{


				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{


				break;
			}
		}
	}
	else // EnemyTurn
	{

	}


	Draw(aWindow);
}

void Battle::Attack()
{

}

void Battle::Defend()
{

}

void Battle::Heal()
{

}

void Battle::UseAbilities()
{

}

void Battle::Draw(sf::RenderWindow& aWindow)
{
	for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
		myPlayerPartyMembers[i]->Draw(aWindow);
	for (size_t i = 0; i < myEnemyPartyMembers.size(); i++)
		myEnemyPartyMembers[i]->Draw(aWindow);

	aWindow.draw(myText);
}