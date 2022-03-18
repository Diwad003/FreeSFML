#include "Game.h"

int main()
{
    sf::Texture myWallTexture;
    myWallTexture.loadFromFile("Sprites/Wall.png");
    sf::RenderWindow tempWindow(sf::VideoMode(myWallTexture.getSize().x, myWallTexture.getSize().y), "SFML works!");
    Game* tempGame = new Game(tempWindow);
    while (tempWindow.isOpen())
    {
        tempGame->Update();
        tempGame->Draw();

        tempWindow.clear();
    }
}