#include "NPC.h"
#include "Dialog.h"
#include <iostream>

NPC::NPC(const std::string& name, int health) : name(name), health(health) {}

void NPC::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Green);
    boundingRectangle.setOutlineThickness(1);
    boundingRectangle.setSize(sf::Vector2f(64, 64));
}

sf::RectangleShape NPC::getBoundingRectangle() const {
    return boundingRectangle;
}

void NPC::Load(const std::string& textureFile) {
    if (texture.loadFromFile(textureFile)) {
        std::cout << "NPC Texture Loaded!" << std::endl;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        sprite.scale(sf::Vector2f(1, 1));
    }
    else {
        std::cerr << "Failed to load NPC texture." << std::endl;
    }
}

void NPC::Update() {
    // Aktualizacja logiki NPC, np. animacje
}

void NPC::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(boundingRectangle);
}

void NPC::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    boundingRectangle.setPosition(x, y);
}

sf::Vector2f NPC::getPosition() const {
    return sprite.getPosition();
}
