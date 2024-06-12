#include "Options.h"

Options::Options(float width, float height) : screenWidth(width), screenHeight(height), currentResolutionIndex(0), currentTextSizeIndex(0) {
    resolutions = { sf::VideoMode(1920, 1080), sf::VideoMode(2560, 1440), sf::VideoMode(3840, 2160) };
    textSizes = { 12, 16, 20, 24 };
}

Options::~Options() {}

void Options::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setString("Options");
    title.setPosition(screenWidth / 2 - title.getGlobalBounds().width / 2, 50);
    window.draw(title);

    sf::Text resolutionText;
    resolutionText.setFont(font);
    resolutionText.setCharacterSize(20);
    resolutionText.setFillColor(sf::Color::White);
    resolutionText.setString("Resolution: " + std::to_string(resolutions[currentResolutionIndex].width) + "x" + std::to_string(resolutions[currentResolutionIndex].height));
    resolutionText.setPosition(100, 150);
    window.draw(resolutionText);

    sf::Text textSizeText;
    textSizeText.setFont(font);
    textSizeText.setCharacterSize(20);
    textSizeText.setFillColor(sf::Color::White);
    textSizeText.setString("Text Size: " + std::to_string(textSizes[currentTextSizeIndex]));
    textSizeText.setPosition(100, 200);
    window.draw(textSizeText);

    window.display();
}

void Options::nextResolution() {
    currentResolutionIndex = (currentResolutionIndex + 1) % resolutions.size();
}

void Options::previousResolution() {
    currentResolutionIndex = (currentResolutionIndex - 1 + resolutions.size()) % resolutions.size();
}

void Options::nextTextSize() {
    currentTextSizeIndex = (currentTextSizeIndex + 1) % textSizes.size();
}

void Options::previousTextSize() {
    currentTextSizeIndex = (currentTextSizeIndex - 1 + textSizes.size()) % textSizes.size();
}

sf::VideoMode Options::getCurrentResolution() const {
    return resolutions[currentResolutionIndex];
}

unsigned int Options::getCurrentTextSize() const {
    return textSizes[currentTextSizeIndex];
}
