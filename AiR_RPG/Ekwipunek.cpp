#include "Ekwipunek.h"
#include <iostream>

Ekwipunek::Ekwipunek(const std::vector<std::string>& items)
    : items(items), selectedItemIndex(0), columns(2), rows((items.size() + 1) / 2) {
}
//Rysowanie ekwipunku
void Ekwipunek::draw(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text itemText;
        itemText.setFont(font);
        itemText.setString(items[i]);
        itemText.setCharacterSize(24);
        itemText.setFillColor(i == selectedItemIndex ? sf::Color::Yellow : sf::Color::White);

        int col = i % columns;
        int row = i / columns;
        itemText.setPosition(400 + col * 200, 300 + row * 30);

        window.draw(itemText);
    }
}
//Sterowanie po ekwipunku
void Ekwipunek::handleInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Left) {
        updateSelection(-1);
    }
    else if (key == sf::Keyboard::Right) {
        updateSelection(1);
    }
    else if (key == sf::Keyboard::Up) {
        updateSelection(-columns);
    }
    else if (key == sf::Keyboard::Down) {
        updateSelection(columns);
    }
}
//Aktualizowanie wyboru
void Ekwipunek::updateSelection(int direction) {
    int newIndex = selectedItemIndex + direction;

    if (newIndex >= 0 && newIndex < items.size()) {
        selectedItemIndex = newIndex;
    }
}
