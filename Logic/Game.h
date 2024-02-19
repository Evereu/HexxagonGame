#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

class Game {

public:

    auto runGame(sf::RenderWindow &window)-> void;
    auto runScore(sf::RenderWindow &window)-> void;

};

