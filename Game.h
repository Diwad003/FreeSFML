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
	sf::View* myView;
	std::vector<sf::Sprite> myWallSprites = std::vector<sf::Sprite>();
	sf::Texture* myWallTexture;

	sf::Clock myDeltaTimeClock;
	float myDeltaTime;
	float myWallAcceleration;
	float myWallVelocity;
};
#endif