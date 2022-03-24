#ifndef ENEMY_PARTY_MEMBER_HEADER
#define ENEMY_PARTY_MEMBER_HEADER

#include "Entity.h"
#include "Party_Member.h"

class Enemy_Party_Member : public Entity
{
public:
	Enemy_Party_Member(sf::Vector2f aPosition, int aHealth, sf::Sprite aSprite, sf::Texture& aTexture, int aDMG, std::vector<Party_Member*>& aPlayerParty);

	void Update();
	bool GetTimeForBattle();

private:
	std::vector<Party_Member*> myPlayerParty;
	bool myTimeForBattle;
};
#endif