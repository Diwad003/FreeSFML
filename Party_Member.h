#ifndef PARTY_MEMBER_HEADER
#define PARTY_MEMBER_HEADER

#include "Entity.h"

class Party_Member : public Entity
{
public:
	Party_Member();
	Party_Member(sf::Vector2f aPosition, int aHealth, sf::Sprite aSprite, sf::Texture &aTexture, int aDMG, Classes aClass);
	void Update();
	Entity::Classes GetClass();
	std::string GetClassStringRepresentation();

protected:
	Classes myClass;

};
#endif