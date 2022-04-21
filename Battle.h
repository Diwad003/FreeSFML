#ifndef BATTLE_HEADER
#define BATTLE_HEADER

#include "Game.h"

class Battle
{
public:
	Battle(std::vector<Party_Member*> &aPartyMembers, std::vector<Enemy_Party_Member*> &aEnemyPartyMembers, sf::Sprite& aWallSprite, sf::RenderWindow*& aWindow);

	void BattleLogic();
	void PressEnterToContinue();
	int ChoosePartyMember();
	void Attacking();
	void Healing();
	void Draw();

	enum BattleSequences { Attack, Heal, Null };

private:
	std::vector<Party_Member*> myPlayerPartyMembers;
	std::vector<Enemy_Party_Member*> myEnemyPartyMembers;
	sf::RenderWindow* myWindow;

	BattleSequences myBattleSequence;
	sf::Sprite myWallSprite;
	bool myPlayerTurn;
	sf::Text myText;
	sf::Font myFont;
};

#endif