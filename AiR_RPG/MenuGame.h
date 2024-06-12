#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MenuGame {
public:
    MenuGame(float width, float height);
    ~MenuGame();

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem();

    void setOptions(const std::vector<std::string>& newOptions);
    void setPosition(float x, float y); // Nowa funkcja do ustawiania pozycji menu

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    float width;
    float height;
    float menuX; // Wsp�rz�dne X menu
    float menuY; // Wsp�rz�dne Y menu
};


