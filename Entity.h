#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include <SFML/Graphics.hpp>

class Entity
{
public:
	enum class Classes { Healer, Warrior };
	enum class Abilities {  };

	Entity();

	void TakeDamage(int aDMG);
	void Heal(int aHealStrenght);
	void SetPosition(sf::Vector2f aMoveTo);
	void Draw(sf::RenderWindow& aWindow);

	sf::Vector2f GetPosition();
	sf::Sprite GetSprite();
	int GetAbilityStrenght();
	int GetHealth();

protected:
	virtual void Update() = 0;


	sf::Vector2f myPosition;
	sf::Texture myTexture;
	int myHealth;
	int myAbilityStrenght;
	sf::Sprite mySprite;
	int myEXP;
	int myAmoutOfEXPToNextLevel;
};
#endif