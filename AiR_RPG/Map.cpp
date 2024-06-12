#include "Map.h"

Map::Map(int rows, int cols, const std::string& floorTexturePath, const std::string& wallTexturePath, const std::string& roadTexturePath)
    : rows(rows), cols(cols)
{
    grid.resize(rows, std::vector<int>(cols, 0));

    if (!floorTexture.loadFromFile(floorTexturePath)) {
        std::cerr << "Failed to load floor textures!" << std::endl;
    }
    else {
        std::cout << "Floor G " << floorTexturePath << std::endl;
    }

    if (!wallTexture.loadFromFile(wallTexturePath)) {
        std::cerr << "Failed to load wall textures!" << std::endl;
    }
    else {
        std::cout << "Wall G " << wallTexturePath << std::endl;
    }

    if (!roadTexture.loadFromFile(roadTexturePath)) {
        std::cerr << "Failed to load road textures!" << std::endl;
    }
    else {
        std::cout << "Road G " << roadTexturePath << std::endl;
    }

    floorSprite.setTexture(floorTexture);
    wallSprite.setTexture(wallTexture);
    roadSprite.setTexture(roadTexture);
}
//Ustawianie mapy
void Map::ustaw_stala_mape(const std::vector<std::vector<int>>& newGrid)
{
    if (newGrid.size() != rows || newGrid[0].size() != cols) {
        std::cerr << "Invalid grid dimensions!" << std::endl;
        return;
    }
    grid = newGrid;
}
//Aktualizacja mapy
void Map::aktualizuj_mape(sf::RenderWindow& window)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 0) {
                floorSprite.setPosition(j * 64, i * 64);
                window.draw(floorSprite);
            }
            else if (grid[i][j] == 1) {
                wallSprite.setPosition(j * 64, i * 64);
                window.draw(wallSprite);
            }
            else if (grid[i][j] == 2) {
                roadSprite.setPosition(j * 64, i * 64);
                window.draw(roadSprite);
            }
        }
    }
}

bool Map::kolizja(const sf::FloatRect& boundingBox)
{
    return false; // Brak kolizji
}
