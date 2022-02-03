#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& aWindow)
{
    myWindow = &aWindow;
    myView = new sf::View(myWindow->getDefaultView());
    myDeltaTime = 0;
    myWallVelocity = 0;
    myWallAcceleration = 0.5f;

    myWallTexture = new sf::Texture();
    myWallTexture->loadFromFile("Sprites/Wall.png");

    const sf::IntRect tempSpriteSize(myWindow->getPosition(), sf::Vector2i(myWindow->getSize().x, myWindow->getSize().y));
    for (int i = 0; i < 2; ++i)
        myWallSprites.push_back(sf::Sprite(*myWallTexture, tempSpriteSize));
}

void Game::Update()
{
    myDeltaTime = myDeltaTimeClock.restart().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        myWindow->close();

#pragma region Wall
    //Wall Movement/Scrolling
    int tempWallSpeed = 10;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && myWallVelocity < 50)
    {
        myWallVelocity += myWallAcceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && myWallVelocity > -50)
    {
        myWallVelocity -= myWallAcceleration;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && myWallVelocity != 0)
    {
        if (myWallVelocity < 0)
        {
            myWallVelocity += myWallAcceleration;
        }
        else
        {
            myWallVelocity -= myWallAcceleration;
        }
    }

    if ((myWallSprites[0].getPosition().x + myWallSprites[0].getTexture()->getSize().x) < 0) //out of screen
    {
        myWallSprites[0].setPosition(int(myWallSprites[1].getPosition().x + myWallSprites[1].getTexture()->getSize().x), 0);
        myWallSprites[1].setPosition(int(myWallSprites[0].getPosition().x - myWallSprites[0].getTexture()->getSize().x), 0);
    }
    if ((myWallSprites[1].getPosition().x + myWallSprites[1].getTexture()->getSize().x < 0)) //out of screen
    {
        myWallSprites[1].setPosition(int(myWallSprites[0].getPosition().x + myWallSprites[0].getTexture()->getSize().x), 0);
        myWallSprites[0].setPosition(int(myWallSprites[1].getPosition().x - myWallSprites[1].getTexture()->getSize().x), 0);
    }

    myWallSprites[0].move(myWallVelocity * myDeltaTime * tempWallSpeed, 0);
    myWallSprites[1].move(myWallVelocity * myDeltaTime * tempWallSpeed, 0);
#pragma endregion
}

void Game::Draw()
{
    for (size_t i = 0; i < myWallSprites.size(); i++)
        myWindow->draw(myWallSprites[i]);



    sf::Text tempText;
    sf::Font tempFont;
    tempFont.loadFromFile("arial.ttf");
    tempText.setFont(tempFont);
    tempText.setCharacterSize(24);
    tempText.setFillColor(sf::Color::Red);
    tempText.setStyle(sf::Text::Bold);


    tempText.setString(std::to_string(myWallVelocity));
    myWindow->draw(tempText);
    tempText.setPosition(sf::Vector2f(0, 20));
    for (size_t i = 0; i < myWallSprites.size(); i++)
        tempText.setString("X " + std::to_string(myWallSprites[i].getPosition().x) + " Y " + std::to_string(myWallSprites[i].getPosition().y));
    myWindow->draw(tempText);



    myWindow->display();
}