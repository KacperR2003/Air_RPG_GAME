#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>

class Enemy : public Character {
public:
    Enemy(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);

    void Initialize();
    void Load();
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void performRandomAttack(Character& opponent);
    void drop();

    sf::RectangleShape getBoundingRectangle() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
};
