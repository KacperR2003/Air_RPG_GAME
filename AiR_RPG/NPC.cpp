#include "NPC.h"
#include <iostream>

NPC::NPC(const std::string& name, int health)
    : name(name), health(health), basicAttackDamage(0), specialAttackDamage(0) {}

NPC::NPC(const std::string& name, int health, int basicAttackDamage, int specialAttackDamage)
    : name(name), health(health), basicAttackDamage(basicAttackDamage), specialAttackDamage(specialAttackDamage) {}

void NPC::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Green);
    boundingRectangle.setOutlineThickness(1);
    boundingRectangle.setSize(sf::Vector2f(64, 64));

    if (!font.loadFromFile("arial.ttf")) { // Za³aduj czcionkê
        std::cerr << "Failed to load font!" << std::endl;
    }

    collisionText.setFont(font);
    collisionText.setCharacterSize(24);
    collisionText.setFillColor(sf::Color::Red);
    collisionText.setString("");

    // Ustawiamy pocz¹tkowe po³o¿enie tekstu
    collisionText.setPosition(100, 100); // Mo¿esz dostosowaæ po³o¿enie wed³ug potrzeb
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

void NPC::Update(sf::RenderWindow& window) {
    // Aktualizacja logiki NPC, np. animacje
}

void NPC::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(boundingRectangle);

    // Rysujemy tekst tylko jeœli kolizja jest wykryta
    if (collisionText.getString() != "") {
        window.draw(collisionText);
    }
}

void NPC::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    boundingRectangle.setPosition(x, y);
}

sf::Vector2f NPC::getPosition() const {
    return sprite.getPosition();
}

sf::RectangleShape NPC::getBoundingRectangle() const {
    return boundingRectangle;
}

bool NPC::CheckCollision(const sf::RectangleShape& other) {
    bool collision = boundingRectangle.getGlobalBounds().intersects(other.getGlobalBounds());
    if (collision) {
        collisionText.setString("Zalatw tego goscia na dole");
    }
    else {
        collisionText.setString("");
    }
    return collision;
}
