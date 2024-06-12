#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Options {
public:
    Options(float width, float height);

    ~Options();

    void draw(sf::RenderWindow& window);

    void nextResolution();

    void previousResolution();

    void nextTextSize();

    void previousTextSize();

    sf::VideoMode getCurrentResolution() const;

    unsigned int getCurrentTextSize() const;

private:
    float screenWidth;
    float screenHeight;
    std::vector<sf::VideoMode> resolutions;
    std::vector<unsigned int> textSizes;
    unsigned int currentResolutionIndex;
    unsigned int currentTextSizeIndex;
    sf::Font font;
};
