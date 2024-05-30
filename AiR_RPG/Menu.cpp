#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        // handle error
        std::cerr << "Error loading font" << std::endl;
    }

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Nowa Gra");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MENU_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Zaladuj");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MENU_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Opcje");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MENU_ITEMS + 1) * 3));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Wyjscie");
    menu[3].setPosition(sf::Vector2f(width / 2, height / (MENU_ITEMS + 1) * 4));

    selectedItemIndex = 0;
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < MENU_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown() {
    if (selectedItemIndex + 1 < MENU_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::GetPressedItem() {
    return selectedItemIndex;
}