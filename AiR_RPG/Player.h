#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>

class Player : public Character {
public:
    Player(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);

    void Initialize();
    void Load();
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    bool CheckCollision(const sf::RectangleShape& other);

    sf::RectangleShape& GetBoundingRectangle();
    void RevertMove();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
    sf::Vector2f lastValidPosition;
};