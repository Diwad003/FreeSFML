#ifndef ENEMY_PARTY_MEMBER_HEADER
#define ENEMY_PARTY_MEMBER_HEADER

#include "Entity.h"
#include "Party_Member.h"

class Enemy_Party_Member : public Party_Member
{
public:
	Enemy_Party_Member(sf::Vector2f aPosition, int aHealth, sf::Sprite aSprite, sf::Texture& aTexture, int aAbilityStrenght, std::vector<Party_Member*>& aPlayerParty, Classes aClass);
	void Update();
	bool* GetTimeForBattle();

private:
	std::vector<Party_Member*> myPlayerParty;
	bool* myTimeForBattle;
};
#endif