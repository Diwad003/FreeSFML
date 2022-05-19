#include "Game.h"
#include <iostream>
#include "Battle.h"

Game::Game(sf::RenderWindow& aWindow)
{
    myWindow = &aWindow;
    myDeltaTime = 0;
    myWallVelocity = 0;
    myTimeForBattle = new bool(false);
    
    //system("dir");

    myFont.loadFromFile("arial.ttf");
    myText.setFont(myFont);
    myText.setCharacterSize(30);
    myText.setFillColor(sf::Color::Black);

    myWallTexture = new sf::Texture();
    myWallTexture->loadFromFile("Sprites/Wall.png");
    
    myWallTexture->setRepeated(true);
    myWallSprite = new sf::Sprite();
    myWallSprite->setTexture(*myWallTexture);
    sf::IntRect tempIntRectangle(0, 0, 100000, myWallTexture->getSize().y);
    myWallSprite->setTextureRect(tempIntRectangle);
    myWallSprite->setPosition(-(tempIntRectangle.width / 2), 0);


    sf::Texture tempPartyLeaderTexture = sf::Texture();
    tempPartyLeaderTexture.loadFromFile("Sprites/PartyLeader.png");
    sf::Sprite tempPlayerPartyLeaderSprite = sf::Sprite();
    tempPlayerPartyLeaderSprite.setScale(0.6f, 0.6f);

    int tempFloorY = 691;
    myPlayerParty.push_back(new Party_Member(
        sf::Vector2f(500, tempFloorY), 1, tempPlayerPartyLeaderSprite, tempPartyLeaderTexture, 1, Entity::Classes::Warrior));

    sf::Texture tempPartyHealerTexture = sf::Texture();
    tempPartyHealerTexture.loadFromFile("Sprites/PlayerHealer.png");
    sf::Sprite tempPartyHealerSprite = sf::Sprite();
    tempPartyHealerSprite.setScale(1.2f, 1.2f);
    myPlayerParty.push_back(new Party_Member(
        sf::Vector2f(300, tempFloorY), 1, tempPartyHealerSprite, tempPartyHealerTexture, 2, Entity::Classes::Healer));


    sf::Texture tempEnemyPartyLeaderTexture = sf::Texture();
    tempEnemyPartyLeaderTexture.loadFromFile("Sprites/EnemyLeader.png");
    sf::Sprite tempEnemyPartyLeaderSprite = sf::Sprite();
    tempEnemyPartyLeaderSprite.setScale(0.6f, 0.6f);
    myEnemyParty.push_back(new Enemy_Party_Member(
        sf::Vector2f(2000, tempFloorY), 1, tempEnemyPartyLeaderSprite, tempEnemyPartyLeaderTexture, 1, myPlayerParty, Entity::Classes::Warrior));

    sf::Texture tempEnemyPartyHealerTexture = sf::Texture();
    tempEnemyPartyHealerTexture.loadFromFile("Sprites/EnemyHealer.png");
    sf::Sprite tempEnemyPartyHealerSprite = sf::Sprite();
    tempEnemyPartyHealerSprite.setScale(1.2f, 1.2f);
    myEnemyParty.push_back(new Enemy_Party_Member(
        sf::Vector2f(2300, tempFloorY), 1, tempEnemyPartyHealerSprite, tempEnemyPartyHealerTexture, 1, myPlayerParty, Entity::Classes::Healer));
}

void Game::Update()
{
    myDeltaTime = myDeltaTimeClock.restart().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        myWindow->close();

    for (size_t i = 0; i < myEnemyParty.size(); i++)
    {
        myEnemyParty[i]->SetPosition(sf::Vector2f(myWallVelocity * myDeltaTime, 0));
        myEnemyParty[i]->Update();
    }

    for (size_t i = 0; i < myEnemyParty.size(); i++)
    {
        myTimeForBattle = myEnemyParty[i]->GetTimeForBattle();
        if (myTimeForBattle)
        {
            Battle tempBattle = Battle(myPlayerParty, myEnemyParty, *myWallSprite, myWindow);
            while (myTimeForBattle)
            {
                tempBattle.BattleLogic(myTimeForBattle);

                if (!*myTimeForBattle)
                {
                    break;
                }
            }

            for (size_t i = 0; i < myPlayerParty.size(); i++)
            {
                myPlayerParty[i]->LevelUp();


                myText.setString("The party member " + myPlayerParty[i]->GetClassStringRepresentation() + " is now level " + std::to_string(myPlayerParty[i]->GetLevel()));
                myWindow->draw(myText);

                myText.setString("PRESS ENTER TO CONTINUE");
                while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        myWindow->close();
                    myWindow->draw(myText);
                }
            }
        }
    }

#pragma region Wall Logic
    //Wall Movement/Scrolling
    float tempWallAcceleration = 0.5f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && myWallVelocity < 100)
    {
        if (myWallVelocity < 0)
        {
            myWallVelocity = 0;
        }
        else
        {
            myWallVelocity += tempWallAcceleration;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && myWallVelocity > -100)
    {
        if (myWallVelocity > 0)
        {
            myWallVelocity = 0;
        }
        else
        {
            myWallVelocity -= tempWallAcceleration;
        }
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && myWallVelocity != 0)
    {
        if (myWallVelocity < 0)
        {
            myWallVelocity += tempWallAcceleration;
        }
        else
        {
            myWallVelocity -= tempWallAcceleration;
        }
    }

    myWallSprite->move(myWallVelocity * myDeltaTime, 0);
#pragma endregion
}

void Game::Draw()
{
    myWindow->draw(*myWallSprite);

    for (size_t i = 0; i < myPlayerParty.size(); i++)
    {
        myPlayerParty[i]->Draw(*myWindow);
    }
    for (size_t i = 0; i < myEnemyParty.size(); i++)
    {
        myEnemyParty[i]->Draw(*myWindow);
    }

    myWindow->display();
}