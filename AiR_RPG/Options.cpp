#include "Options.h"
#include <iostream>

Options::Options(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White); // Zmieniamy kolor tekstu na bia³y
    menu[0].setString("1920 x 1080");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("2560 x 1440");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("3840 x 2160");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 3));

    selectedItemIndex = 0;
}


Options::~Options() {}
//Rysowanie opcji
void Options::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(menu[i]);
    }
}

//Poruszanie w góre
void Options::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
//Poruszanie w dó³
void Options::MoveDown() {
    if (selectedItemIndex + 1 < 3) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
//wybór opcji
int Options::GetPressedItem() {
    return selectedItemIndex;
}
