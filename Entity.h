#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	Entity(sf::Vector2f aPosition, int aHealth, sf::Sprite aSprite, int aDMG);

	void TakeDamage(int aDMG);

protected:
	sf::Vector2f myPosition;
	sf::Texture myTexture;
	int myHealth;
	int myDMG;
	sf::Sprite mySprite;
};
#endif