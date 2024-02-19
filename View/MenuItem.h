#pragma once
#include "SFML/Graphics.hpp"
class MenuItem {

public:

    MenuItem(std::string itemText, float positionX, float positionY);

    ~ MenuItem();

    auto createMenuItem(sf::RenderWindow &window, int winSizeX, int winSizeY) -> sf::Sprite;

    sf::Sprite sprite;
    sf::RectangleShape rectangle;
    sf::Font font;
    sf::Text text;
    sf::RenderTexture renderTexture;

private:
    std::string itemText;
    float positionX;
    float positionY;

};

