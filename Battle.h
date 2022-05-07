#ifndef BATTLE_HEADER
#define BATTLE_HEADER

#include "Game.h"

class Battle
{
public:
	enum BattleSequences { Attack, Heal, Null };

	Battle(std::vector<Party_Member*> &aPartyMembers, std::vector<Enemy_Party_Member*> &aEnemyPartyMembers, sf::Sprite& aWallSprite, sf::RenderWindow*& aWindow);

	void BattleLogic(bool &aTimeForBattle);
	int ChoosePartyMember(int& tempChosenPartyMember);
	void Attacking();
	void Healing();
	void Draw();
	void PressEnterToContinue();
	void ProcessDeadEnemies();
	void ProcessDeadPlayers();

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