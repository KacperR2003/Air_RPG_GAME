#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <string>

class NPC {
public:
    NPC(const std::string& name, int health);
    NPC(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage);

    void Initialize();
    void Load(const std::string& textureFile);
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::RectangleShape getBoundingRectangle() const;
    bool CheckCollision(const sf::RectangleShape& other);

private:
    std::string name;
    int health;
    int basicAttackDamage;
    int specialAttackDamage;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
    sf::Font font;
    sf::Text collisionText;
};

#endif // NPC_H
