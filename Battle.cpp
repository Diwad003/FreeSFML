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
		std::string tempString = "You are in a battle with the enemy, press on the respective number for the action you want to do:\n1: Attack\n";
		for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
		{
			if (myPlayerPartyMembers[i]->GetClass() == Entity::Classes::Healer)
			{
				std::string str2("2: Heal\n");
				if (!(tempString.find(str2) != std::string::npos)) 
				{
					tempString += "2: Heal\n";
				}
			}
		}

		myText.setString(tempString);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			tempString = "You are currently in attack, which party member do you want to attack with?\n";
			for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
			{
				tempString = std::to_string(i) + ". " + myPlayerPartyMembers[i]->GetClassStringRepresentation();
			}

			while (true)
			{
				Party_Member tempAttackingPartyMember;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					tempAttackingPartyMember = *myPlayerPartyMembers[0];
					break;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					tempAttackingPartyMember = *myPlayerPartyMembers[1];
					break;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					tempAttackingPartyMember = *myPlayerPartyMembers[2];
					break;
				}
			}




			Enemy_Party_Member tempFirstEnemy = *myEnemyPartyMembers[0];
			Party_Member tempFirstPlayer = *myPlayerPartyMembers[0];

			tempFirstEnemy.TakeDamage(tempFirstPlayer.GetDamage());
			myPlayerTurn = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			//IMPLEMENT HEALING WITH HEALING ITEMS
			myPlayerTurn = false;
		}
	}
	else // EnemyTurn
	{
		int tempRNG = rand() % 3 + 1;
		if (tempRNG == 1)
		{
			Enemy_Party_Member tempFirstEnemy = *myEnemyPartyMembers[0];
			Party_Member tempFirstPlayer = *myPlayerPartyMembers[0];

			tempFirstPlayer.TakeDamage(tempFirstEnemy.GetDamage());
		}
		else if (tempRNG == 2)
		{

		}
		else
		{

		}
	}


	Draw(aWindow);
}

void Battle::Draw(sf::RenderWindow& aWindow)
{
	for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
		myPlayerPartyMembers[i]->Draw(aWindow);
	for (size_t i = 0; i < myEnemyPartyMembers.size(); i++)
		myEnemyPartyMembers[i]->Draw(aWindow);

	aWindow.draw(myText);
}