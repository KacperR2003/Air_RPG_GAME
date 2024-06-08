#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Ekwipunek {
public:
    Ekwipunek(const std::vector<std::string>& items);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Keyboard::Key key);

private:
    std::vector<std::string> items;
    int selectedItemIndex;
    int columns;
    int rows;

    void updateSelection(int direction);
};




