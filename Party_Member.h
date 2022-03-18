#ifndef PARTY_MEMBER
#define PARTY_MEMBER

#include "Entity.h"

class Party_Member : public Entity
{
public:
	Party_Member(sf::Vector2f aPosition, int aHealth, sf::Texture aTexture, int aDMG);

	void Update();
	void SetPosition(sf::Vector2f aMoveTo);
	void Draw(sf::RenderWindow& aWindow);

private:

};
#endif