#ifndef GAME_HEADER
#define GAME_HEADER

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(sf::RenderWindow& aWindow);
	void Update();
	void Draw();

private:
	sf::RenderWindow* myWindow;
	sf::Clock myDeltaTimeClock;
	float myDeltaTime;

	std::vector<sf::Sprite> myWallSprites = std::vector<sf::Sprite>();
	float myWallAcceleration;
	float myWallVelocity;
};
#endif