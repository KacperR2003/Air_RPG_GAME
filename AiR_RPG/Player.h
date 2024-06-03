#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public Character
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
    sf::Vector2f lastValidPosition; // Dodany wektor przechowuj�cy ostatni� poprawn� pozycj� gracza

public:
    void Load();
    void Update(sf::RenderWindow& window);
    void Initialize();
    void Draw(sf::RenderWindow& window);
    void flee();
    void gain_exp();
    bool CheckCollision(const sf::RectangleShape& other);
    Player(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);
    sf::RectangleShape& GetBoundingRectangle(); // Funkcja zwracaj�ca referencj� do prostok�ta kolizji gracza
    void RevertMove(); // Funkcja cofaj�ca ostatni ruch gracza w przypadku kolizji
};

