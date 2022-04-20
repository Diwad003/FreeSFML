#include "Battle.h"

Battle::Battle(std::vector<Party_Member*>& aPartyMembers, std::vector<Enemy_Party_Member*>& aEnemyPartyMembers, sf::Sprite& aWallSprite, sf::RenderWindow*& aWindow)
{
	myPlayerPartyMembers = aPartyMembers;
	myEnemyPartyMembers = aEnemyPartyMembers;
	myWallSprite = aWallSprite;
	myPlayerTurn = true;
	myBattleSequence = BattleSequences::Null;
	myWindow = aWindow;


	myFont.loadFromFile("arial.ttf");
	myText.setFont(myFont);
	myText.setCharacterSize(30);
	myText.setFillColor(sf::Color::Black);


	//sf::Vector2f tempPosition = sf::Vector2f(myPlayerPartyMembers[0]->GetPosition().x - 100, 691);
	//myPlayerPartyMembers[0]->GetSprite().setPosition(tempPosition);
	//for (size_t i = 1; i < myPlayerPartyMembers.size(); i++)
	//{
	//	myPlayerPartyMembers[i]->GetSprite().setPosition(myPlayerPartyMembers[i - 1]->GetPosition().x + myPlayerPartyMembers[i]->GetSprite().getScale().x, 0);
	//}

/*	tempPosition = sf::Vector2f(2000, 691);
	for (size_t i = 0; i < myEnemyPartyMembers.size(); i++)
	{
		if (i > 0)
		{
			tempPosition.x += myEnemyPartyMembers[i - 1]->GetSprite().getScale().x;
		}
		myEnemyPartyMembers[i]->SetPosition(tempPosition);
	}*/
}

void Battle::BattleLogic()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		myWindow->close();

	if (myBattleSequence == BattleSequences::Null)
	{
		if (myPlayerTurn)
		{
			std::string tempString = "You are in a battle with the enemy, press on the respective number for the action you want to do:\n1: Attack\n";
			for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
			{
				if (myPlayerPartyMembers[i]->GetClass() == Entity::Classes::Healer)
				{
					if (tempString.find("2: Heal\n") == std::string::npos)
					{
						tempString += "2: Heal\n";
					}
				}
			}


			myText.setString(tempString);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				myBattleSequence = BattleSequences::Attack;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				myBattleSequence = BattleSequences::Heal;
			}
		}
		//else // EnemyTurn
		//{
		//	//int tempRNG = rand() % 3 + 1;
		//	//if (tempRNG == 1)
		//	//{
		//	//	Enemy_Party_Member tempFirstEnemy = *myEnemyPartyMembers[0];
		//	//	Party_Member tempFirstPlayer = *myPlayerPartyMembers[0];

		//	//	tempFirstPlayer.TakeDamage(tempFirstEnemy.GetDamage());
		//	//}
		//	/*else if (tempRNG == 2)
		//	{

		//	}
		//	else
		//	{

		//	}*/
		//}
	}
	else if (myBattleSequence == BattleSequences::Attack)
	{
		Attacking();
	}
	else if (myBattleSequence == BattleSequences::Heal)
	{
		//IMPLEMENT HEALING WITH HEALING SPELLS OR SOMETHING
	}


	Draw();
}

void Battle::PressEnterToContinue()
{
	myText.setString("PRESS ENTER TO CONTINUE");
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			myWindow->close();
		Draw();
	}
}

int Battle::ChoosePartyMember()
{
	int tempEnemyToAttack = 4;
	while (tempEnemyToAttack == 4)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			tempEnemyToAttack = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			tempEnemyToAttack = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			tempEnemyToAttack = 2;
		}
	}

	return tempEnemyToAttack;
}

void Battle::Attacking()
{
	PressEnterToContinue();


	std::string tempString = "You are currently in attack, which party member do you want to attack with?\n";
	for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
	{
		tempString += std::to_string(i) + ". " + myPlayerPartyMembers[i]->GetClassStringRepresentation() + "\n";
	}
	myText.setString(tempString);
	myWindow->draw(myText);
	Party_Member tempAttackingPartyMember = *myPlayerPartyMembers[ChoosePartyMember()];


	PressEnterToContinue();


	std::string tempString = "Which enemy do you want to attack?\n";
	for (size_t i = 0; i < myEnemyPartyMembers.size(); i++)
	{
		tempString += std::to_string(i) + ". " + myEnemyPartyMembers[i]->GetClassStringRepresentation() + "\n";
	}
	myText.setString(tempString);
	myWindow->draw(myText);
	Enemy_Party_Member tempEnemyThatIsAttacked = *myEnemyPartyMembers[ChoosePartyMember()];

	
	PressEnterToContinue();


	std::string tempString = "You attack with your " + tempAttackingPartyMember.GetClassStringRepresentation() +
		" against enemy " + tempEnemyThatIsAttacked.GetClassStringRepresentation() + " and damaged " + std::to_string(tempAttackingPartyMember.GetDamage()) + ".\n" +
		" the enemy has " + std::to_string((tempEnemyThatIsAttacked.GetHealth() - tempAttackingPartyMember.GetDamage()));

	tempEnemyThatIsAttacked.TakeDamage(tempAttackingPartyMember.GetDamage());

	myPlayerTurn = false;
}

void Battle::Draw()
{
	myWindow->draw(myWallSprite);
	for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
	{
		myPlayerPartyMembers[i]->Draw(*myWindow);
	}
	for (size_t i = 0; i < myEnemyPartyMembers.size(); i++)
	{
		myEnemyPartyMembers[i]->Draw(*myWindow);
	}

	myWindow->draw(myText);
	myWindow->display();
}