#include "MenuGame.h"
#include <iostream>

MenuGame::MenuGame(float width, float height) : width(width), height(height), selectedItemIndex(0), menuX(0), menuY(0) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
}

MenuGame::~MenuGame() {}

void MenuGame::setOptions(const std::vector<std::string>& newOptions) {
    menuItems.clear();

    for (size_t i = 0; i < newOptions.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(newOptions[i]);
        text.setCharacterSize(20); // Zmniejszamy rozmiar tekstu
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

        // Ustawiamy pozycjê na podstawie pozycji menuX, menuY
        text.setPosition(sf::Vector2f(menuX, menuY + i * (text.getCharacterSize() + 10)));
        menuItems.push_back(text);
    }
    selectedItemIndex = 0;
}

void MenuGame::setPosition(float x, float y) {
    menuX = x;
    menuY = y;

    // Aktualizujemy pozycje elementów menu po zmianie wspó³rzêdnych
    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].setPosition(sf::Vector2f(menuX, menuY + i * (menuItems[i].getCharacterSize() + 10)));
    }
}

void MenuGame::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void MenuGame::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void MenuGame::MoveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int MenuGame::GetPressedItem() {
    return selectedItemIndex;
}