#include "Game.h"

Game::Game(sf::RenderWindow& aWindow)
{
    myWindow = &aWindow;
    myDeltaTime = 0;
    myWallVelocity = 0;
    

    myWallTexture = new sf::Texture();
    myWallTexture->loadFromFile("Sprites/Wall.png");
    
    myWallTexture->setRepeated(true);
    mySprite = new sf::Sprite();
    mySprite->setTexture(*myWallTexture);
    sf::IntRect tempIntRectangle(0, 0, 100000, myWallTexture->getSize().y);
    mySprite->setTextureRect(tempIntRectangle);
    mySprite->setPosition(-(tempIntRectangle.width / 2), 0);
}

void Game::Update()
{
    myDeltaTime = myDeltaTimeClock.restart().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        myWindow->close();

#pragma region Wall Logic
    //Wall Movement/Scrolling
    float tempWallAcceleration = 0.5f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && myWallVelocity < 300)
    {
        myWallVelocity += tempWallAcceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && myWallVelocity > -300)
    {
        myWallVelocity -= tempWallAcceleration;
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

    mySprite->move(myWallVelocity * myDeltaTime, 0);
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

    //tempText.setString("SPRITE X: " + std::to_string(mySprite->getPosition().x) + "\nY: " + std::to_string(mySprite->getPosition().y) + "\nmyWallVelocity" + std::to_string(myWallVelocity));

    myWindow->draw(*mySprite);
    myWindow->draw(tempText);

    myWindow->display();
}