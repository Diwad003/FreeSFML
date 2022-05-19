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
}

void Battle::BattleLogic(bool* &aTimeForBattle)
{
	if (myEnemyPartyMembers.size() == 0 || myPlayerPartyMembers.size() == 0)
	{
		aTimeForBattle = new bool(false);
		return;
	}

	Draw();

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
		else
		{
			myPlayerTurn = true;	//ENEMY AI
		}
	}
	else if (myBattleSequence == BattleSequences::Attack)
	{
		Attacking();
	}
	else if (myBattleSequence == BattleSequences::Heal)
	{
		Healing();
	}
}

int Battle::ChoosePartyMember(int &tempChosenPartyMember)
{
	int tempPartyMember = 4;
	while (tempPartyMember == 4)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			tempPartyMember = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			tempPartyMember = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			tempPartyMember = 2;
		}
	}

	tempChosenPartyMember = tempPartyMember;
	return tempChosenPartyMember;
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
	Draw();
	int tempChosenPartyMember;
	Party_Member* tempAttackingPartyMember = myPlayerPartyMembers[ChoosePartyMember(tempChosenPartyMember)];


	PressEnterToContinue();


	tempString = "Which enemy do you want to attack?\n";
	for (size_t i = 0; i < myEnemyPartyMembers.size(); i++)
	{
		tempString += std::to_string(i) + ". " + myEnemyPartyMembers[i]->GetClassStringRepresentation() + "\n";
	}
	myText.setString(tempString);
	Draw();
	int tempChosenEnemyPartyMember;
	Enemy_Party_Member* tempEnemyThatIsAttacked = myEnemyPartyMembers[ChoosePartyMember(tempChosenEnemyPartyMember)];

	
	PressEnterToContinue();


	tempString = "You attack with your " + tempAttackingPartyMember->GetClassStringRepresentation() +
		" against enemy " + tempEnemyThatIsAttacked->GetClassStringRepresentation() + " and damaged " + std::to_string(tempAttackingPartyMember->GetAbilityStrenght()) + ".\n" +
		" the enemy has " + std::to_string((tempEnemyThatIsAttacked->GetHealth() - tempAttackingPartyMember->GetAbilityStrenght())) + " health." + "\n" +
		"PRESS 1 TO CONTINUE";
	myText.setString(tempString);
	Draw();
	tempEnemyThatIsAttacked->TakeDamage(tempAttackingPartyMember->GetAbilityStrenght());
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			myWindow->close();
		Draw();
	}

	myPlayerTurn = false;
	myBattleSequence = BattleSequences::Null;

	ProcessDead();
}

void Battle::Healing()
{
	PressEnterToContinue();


	std::string tempString = "You are currently in healing, which party member do you want to healing with?\n";
	for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
	{
		if (myPlayerPartyMembers[i]->GetClassStringRepresentation() == "Healer")
		{
			tempString += std::to_string(i) + ". " + myPlayerPartyMembers[i]->GetClassStringRepresentation() + "\n";
		}
	}
	myText.setString(tempString);
	Draw();
	int tempChosenPartyMember;
	Party_Member tempHealingPartyMember = *myPlayerPartyMembers[ChoosePartyMember(tempChosenPartyMember)];


	PressEnterToContinue();


	tempString = "Which frendly entity do you want to heal?\n";
	for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
	{
		tempString += std::to_string(i) + ". " + myPlayerPartyMembers[i]->GetClassStringRepresentation() + "\n";
	}
	myText.setString(tempString);
	Draw();
	int tempChosenEnemyPartyMember;
	Party_Member tempEntityToHeal = *myPlayerPartyMembers[ChoosePartyMember(tempChosenEnemyPartyMember)];


	PressEnterToContinue();


	tempString = "You heal with your " + tempHealingPartyMember.GetClassStringRepresentation() + " and heal stenght is " + std::to_string(tempHealingPartyMember.GetAbilityStrenght()) + ".\n" +
		" the your friendly entity has " + std::to_string((tempEntityToHeal.GetHealth() + tempHealingPartyMember.GetAbilityStrenght())) + " health." + "\n" + "PRESS 1 TO CONTINUE";
	myText.setString(tempString);
	Draw();
	tempEntityToHeal.Heal(tempHealingPartyMember.GetAbilityStrenght());
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			myWindow->close();
		Draw();
	}


	myPlayerTurn = false;
	myBattleSequence = BattleSequences::Null;
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
		myWindow->draw(myEnemyPartyMembers[i]->GetSprite());
		//myEnemyPartyMembers[i]->Draw(*myWindow);
	}

	myWindow->draw(myText);
	myWindow->display();
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

void Battle::ProcessDead()
{
	for (size_t i = 0; i < myPlayerPartyMembers.size(); i++)
	{
		if (myPlayerPartyMembers[i]->GetHealth() <= 0)
		{
			delete(myPlayerPartyMembers[i]);
			myPlayerPartyMembers.erase(myPlayerPartyMembers.begin() + i);
		}
	}


	for (size_t i = 0; i < myEnemyPartyMembers.size(); i++)
	{
		if (myEnemyPartyMembers[i]->GetHealth() <= 0)
		{
			int tempEXPToAdd = myEnemyPartyMembers[i]->GetAbilityStrenght() * 2;
			for (size_t j = 0; j < myPlayerPartyMembers.size(); j++)
			{
				myPlayerPartyMembers[j]->AddToEXP(tempEXPToAdd);
			}

			delete(myEnemyPartyMembers[i]);
			myEnemyPartyMembers.erase(myEnemyPartyMembers.begin() + i);
		}
	}
}