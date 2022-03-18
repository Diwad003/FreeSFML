#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& aWindow)
{
    myWindow = &aWindow;
    myDeltaTime = 0;
    myWallVelocity = 0;
    
    //system("dir");

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
    myPartyLeader = new Party_Member(sf::Vector2f(-(tempIntRectangle.width / 2), 0), 1, tempPartyLeaderTexture, 1);
}

void Game::Update()
{
    myDeltaTime = myDeltaTimeClock.restart().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        myWindow->close();

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
    myPartyLeader->SetPosition(sf::Vector2f(myWallVelocity * myDeltaTime, 0));
#pragma endregion


}

void Game::Draw()
{
    sf::Text tempText;
    sf::Font tempFont;
    tempFont.loadFromFile("arial.ttf");
    tempText.setFont(tempFont);
    tempText.setCharacterSize(24);
    tempText.setFillColor(sf::Color::Red);
    tempText.setStyle(sf::Text::Bold);

    tempText.setString("TEXTURE");

    myWindow->draw(*myWallSprite);
    myWindow->draw(tempText);
    myPartyLeader->Draw(*myWindow);

    myWindow->display();
}