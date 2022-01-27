#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& aWindow)
{
    myWindow = &aWindow;
    myDeltaTime = 0;
    myWallVelocity = 0;
    myWallAcceleration = 0.5f;
    
    for (size_t i = 0; i < 3; i++)
        myWallSprites.push_back(sf::Sprite());
}

void Game::Update()
{
    myDeltaTime = myDeltaTimeClock.restart().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        myWindow->close();

#pragma region Wall
    //Wall Movement/Scrolling
    int myWallSpeed = 10;
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
    myWallSprites[0].move(sf::Vector2f(myWallVelocity * myDeltaTime * myWallSpeed, 0));//STARTS AT MIDDLE 
    myWallSprites[1].setPosition(sf::Vector2f(myWallSprites[0].getPosition().x + myWallSprites[0].getTextureRect().width, 0));//STARTS AT RIGHT SIDE
    myWallSprites[2].setPosition(sf::Vector2f(myWallSprites[0].getPosition().x - myWallSprites[0].getTextureRect().width, 0));//STARTS AT LEFT SIDE

    //int tempTextureWidth = myWallSprites[0].getTextureRect().width;
    //for (size_t i = 0; i < myWallSprites.size(); i++)
    //{
    //    if (i != 0)
    //    {
    //        if (myWallSprites[i-1].getPosition().x > myWindow->getSize().x)
    //        {
    //            myWallSprites[i].setPosition(sf::Vector2f(myWallSprites[i - 1].getPosition().x + tempTextureWidth, 0));
    //        }
    //    }

    }


    sf::View View(myWindow->getDefaultView());


    View.move(-0.2f, -0.3f); // just move the view here in any direction-the tiles will follow automatically
    const sf::Vector2f viewOffset(viewStart - View.getCenter());
    sf::Vector2f spriteOffset;
    spriteOffset.x = floor(viewOffset.x / Texture.getSize().x) * Texture.getSize().x;
    spriteOffset.y = floor(viewOffset.y / Texture.getSize().y) * Texture.getSize().y;
    Sprite.setPosition(spriteStart - spriteOffset);


#pragma endregion


}

void Game::Draw()
{
    sf::Texture myWallTexture;
    myWallTexture.loadFromFile("Sprites/Wall.png");
    for (size_t i = 0; i < myWallSprites.size(); i++)
    {
        myWallSprites[i].setTexture(myWallTexture);
        myWindow->draw(myWallSprites[i]);
    }



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
    {
        tempText.setString("X " + std::to_string(myWallSprites[i].getPosition().x) + " Y " + std::to_string(myWallSprites[i].getPosition().y));
        myWindow->draw(tempText);
        if (i != 0)
        {
            tempText.setPosition(sf::Vector2f(0, 70 * i));
        }
        else
        {
            tempText.setPosition(sf::Vector2f(0, 40));
        }
    }




    myWindow->display();
}