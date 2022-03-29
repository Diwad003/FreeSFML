#ifndef BATTLE_HEADER
#define BATTLE_HEADER

#include "Game.h"

class Battle
{
public:
	Battle(std::vector<Party_Member*> &aPartyMembers, std::vector<Enemy_Party_Member*> &aEnemyPartyMembers, sf::Sprite& aWallSprite);

	void BattleLogic(sf::RenderWindow& aWindow);
	void Attack();
	void Defend();
	void Heal();
	void UseAbilities();
	void Draw(sf::RenderWindow& aWindow);

private:
	std::vector<Party_Member*> myPlayerPartyMembers;
	std::vector<Enemy_Party_Member*> myEnemyPartyMembers;
	sf::Sprite myWallSprite;
	bool myPlayerTurn;
	sf::Text myText;
	sf::Font myFont;
};

#endif