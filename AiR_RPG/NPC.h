#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include "Dialog.h"
#include <string>

class NPC {
public:
    NPC(const std::string& name, int health);

    void Initialize();
    void Load(const std::string& textureFile);
    void Update();
    void Draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::RectangleShape getBoundingRectangle() const;

private:
    std::string name;
    int health;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
};

#endif // NPC_H
