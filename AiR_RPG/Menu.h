#pragma once
#include <SFML/Graphics.hpp>
const int MENU_ITEMS = 4;
class Menu 
{
    public:
        Menu(float width, float height);
        ~Menu();

        void draw(sf::RenderWindow& window);
        void MoveUp();
        void MoveDown();
        int GetPressedItem();

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MENU_ITEMS];
    };

