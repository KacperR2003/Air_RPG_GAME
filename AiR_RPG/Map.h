#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Map
{
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> grid; // 0 - pod�oga, 1 - �ciana, 2 - droga
    sf::Texture floorTexture;
    sf::Texture wallTexture;
    sf::Texture roadTexture;
    sf::Sprite floorSprite;
    sf::Sprite wallSprite;
    sf::Sprite roadSprite;
    std::vector<sf::RectangleShape> wallColliders; // Wektor prostok�t�w kolizji dla �cian

public:
    Map(int rows, int cols, const std::string& floorTexturePath, const std::string& wallTexturePath, const std::string& roadTexturePath);
    void ustaw_stala_mape(const std::vector<std::vector<int>>& newGrid);
    void aktualizuj_mape(sf::RenderWindow& window);
    bool kolizja(const sf::FloatRect& boundingBox);
};
