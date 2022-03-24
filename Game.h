#ifndef GAME_HEADER
#define GAME_HEADER

#include <SFML/Graphics.hpp>
#include "Party_Member.h"
#include "Enemy_Party_Member.h"

class Game
{
public:
	Game(sf::RenderWindow& aWindow);
	void Update();
	void Draw();

	void BattleLoop();

private:
	sf::RenderWindow* myWindow;
	sf::Texture* myWallTexture;
	sf::Sprite* myWallSprite;

	std::vector<Party_Member*> myPlayerParty;
	std::vector<Enemy_Party_Member*> myEnemyParty;


	sf::Clock myDeltaTimeClock;
	float myDeltaTime;
	float myWallVelocity;

	bool myTimeForBattle;
};
#endif