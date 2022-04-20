#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include <SFML/Graphics.hpp>

class Entity
{
public:
	enum class Classes { Healer, Warrior };

	Entity();

	void TakeDamage(int aDMG);
	void SetPosition(sf::Vector2f aMoveTo);
	void Draw(sf::RenderWindow& aWindow);

	sf::Vector2f GetPosition();
	sf::Sprite GetSprite();
	int GetDamage();
	int GetHealth();

protected:
	virtual void Update() = 0;


	sf::Vector2f myPosition;
	sf::Texture myTexture;
	int myHealth;
	int myDMG;
	sf::Sprite mySprite;
};
#endif