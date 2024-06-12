#pragma once
#include <SFML/Graphics.hpp>

class Options {
public:
    Options(float width, float height);
    ~Options();

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem();

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[3];
};
