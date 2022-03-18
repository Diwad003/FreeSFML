#ifndef GAME_HEADER
#define GAME_HEADER

#include <SFML/Graphics.hpp>
#include "Party_Member.h"

class Game
{
public:
	Game(sf::RenderWindow& aWindow);
	void Update();
	void Draw();

private:
	sf::RenderWindow* myWindow;
	sf::Texture* myWallTexture;
	sf::Sprite* myWallSprite;
	Party_Member* myPartyLeader;


	sf::Clock myDeltaTimeClock;
	float myDeltaTime;
	float myWallVelocity;
};
#endif