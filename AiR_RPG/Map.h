#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Map {
public:
    Map(int rows, int cols, const std::string& floorTexturePath, const std::string& wallTexturePath, const std::string& roadTexturePath);
    void ustaw_stala_mape(const std::vector<std::vector<int>>& newGrid);
    void aktualizuj_mape(sf::RenderWindow& window);
    bool kolizja(const sf::FloatRect& boundingBox);

private:
    int rows, cols;
    std::vector<std::vector<int>> grid;
    std::vector<sf::RectangleShape> wallColliders;

    sf::Texture floorTexture;
    sf::Texture wallTexture;
    sf::Texture roadTexture;
    sf::Sprite floorSprite;
    sf::Sprite wallSprite;
    sf::Sprite roadSprite;
};

#endif // MAP_H
